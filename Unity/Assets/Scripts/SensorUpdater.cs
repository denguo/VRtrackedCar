using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System;
using MathNet.Numerics;
using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Single;

public class SensorUpdater : MonoBehaviour {
	public const string COM_NUMBER = "COM7";
	public const int BAUDRATE = 38400;
	public const int PSOC_CLK = 24000;
	public const float T = 8.33f;

	public const float IN_TO_M = 0.0254f;
	public const int N_SENSORS = 4;
	public const float box_height = 0.28f;
	public const float lighthouse_height = 1.0414f;
	public const int S_CHARACTER = 115;
	public const int DT_BOUND = 150000;
	public const float CAR_BOUND = 0.5f;

	public const float left = 122f;
	public const float mid = 182f;
	public const float right = 212f;

	public const float l = -1f;
	public const float m = 0f;
	public const float r = 1f;

	public const float lev1 = 95f;
	public const float lev2 = 127f;
	public const float lev3 = 149f;

	public const float l1 = 1f;
	public const float l2 = 0f;
	public const float l3 = -1f;

	static SerialPort sp = new SerialPort(COM_NUMBER, BAUDRATE);

	private float[] beta = new float[4];
	private float[] theta = new float[4];

	/*
	private float len_01 = 8.7f;
	private float len_12 = 6.75f;
	private float len_02 = 6.9f;

	private bool firstUpdate = true;
	private Vector3 globalOffset = new Vector3();
	private float prevX = float.PositiveInfinity;
	private float prevY = float.PositiveInfinity;
	private float firstY = 0f;
	*/

	private Vector3 lastPos = new Vector3 ();
	private Vector3 lastlastPos = new Vector3 ();

	private float xCorrect;
	private float zCorrect;

	private bool firstX;
	private bool firstZ;
	private float startX;
	private float startZ;
	private bool sensor1;

	// Use this for initialization
	void Start () {
		if (sp != null) {
			Debug.Log ("port not null");
			if (sp.IsOpen) {
				Debug.Log ("port already open");
				sp.Close ();
			}
		}
		sp.Open();
		sp.ReadTimeout = 1;

		Vector3 initPos = transform.position;
		lastPos.Set (initPos.x, initPos.y, initPos.z);
		lastlastPos.Set (initPos.x, initPos.y, initPos.z);

		//lastPos.Set (0f, 0f, 0.001f);
		//lastlastPos.Set (0f, 0f, 0f);

		//xCorrect = 0f;
		//zCorrect = 0f;
		firstZ = true;
		startZ = 0f;
		sensor1 = false;

		//test hardcoded
		//float[] x_test = { 5.15, 4.8, 5.05 };
		//float[] y_test = { 3.5, 3.55, 3.4  };

		//float[] x_test = { 4.1f, 3.7f, 3.9f };
		//float[] y_test = { 3.8f, 3.8f, 3.7f };

		//Vector<float> r_test = triangulatePosition (toAngleRadians (x_test), toAngleRadians (y_test));
		//Debug.Log (r_test.At (0));
		//Debug.Log (r_test.At (1));
		//Debug.Log (r_test.At (2));
	}

	// Update is called once per frame
	void Update () {
		//Debug.Log ("update");

		if (sp.IsOpen) {
			try {
				if (Convert.ToInt32 (sp.ReadByte ()) != S_CHARACTER) return;
				//while (Convert.ToInt32 (sp.ReadByte ()) != S_CHARACTER) {
				//}
				//Debug.Log ("s found");

				int id = sp.ReadByte ();
				if (id > N_SENSORS - 1) {
					Debug.Log ("invalid id: " + id);
					transform.SetPositionAndRotation (lastPos, transform.rotation);
					return;
				}

				//if (id == 0) {
				int axis = sp.ReadByte ();
				if (axis > 1) {
					Debug.Log ("invalid axis: " + axis);
					transform.SetPositionAndRotation (lastPos, transform.rotation);
					return;
				}

				int dt = (sp.ReadByte () << 0) + (sp.ReadByte () << 8) + (sp.ReadByte () << 16);
				if (dt > DT_BOUND) {
					Debug.Log ("dt count out of bounds: " + dt);
					transform.SetPositionAndRotation (lastPos, transform.rotation);
					return;
				}

				if (axis == 0) {        // x sweep
					//theta [id] = dtToAngle (dt);
					if (id == 0) {
						xCorrect = dtToAngle (dt);
						Debug.Log ("id = " + id + " axis= " + axis + " dy: " + dt);
					}
				}
				else {
					if (id == 0) {
						zCorrect = dtToAngle (dt); 
						Debug.Log ("id = " + id + " axis= " + axis + " dy: " + dt);
					}
				}
				//}
			} 
			catch (System.Exception) {
				throw;
			}
		} 
		else {
			Debug.Log ("port not open on update");
		}

		Vector3 newPos = new Vector3 ();
		double errlimit = 0.1;
		bool correct = false;

		newPos.Set (lastPos.x, lastPos.y, lastPos.z);
		if (xCorrect >= 0f) {
			float x = getX (xCorrect);
			//Debug.Log (x);
			if (Math.Abs (lastPos.x - x) > errlimit) {
				newPos.x = x;
				correct = true;
			}
			xCorrect = -1f;
		}

		if (zCorrect >= 0f) {
			float z = getZ (zCorrect);
			if (Math.Abs (lastPos.z - z) > errlimit) {
				newPos.z = z;
				correct = true;
			}
			zCorrect = -1f;
		}

		if (!correct) {
			// Dead-reckon position
			float amountToMove = (lastPos - lastlastPos).magnitude * 0.1f;

			Vector3 diff = lastPos - lastlastPos;
			diff.Normalize ();

			newPos = lastPos + amountToMove * diff;
			if (Math.Abs ((newPos - lastPos).magnitude) < 0.2)
				return;

			transform.SetPositionAndRotation (newPos, transform.rotation);
			lastlastPos = lastPos;
			lastPos = newPos;
			return;
		}
		transform.SetPositionAndRotation (newPos, transform.rotation);
		lastlastPos = lastPos;
		lastPos = newPos;
		return;
	}

	float getX(float xCorrect) {
		float x;
		if (xCorrect > left && xCorrect <= mid) {
			float a = (xCorrect - left) / (mid - left);
			x = a * m + (1f - a) * l;
		} else {
			float a = (right - xCorrect) / (right - mid);
			x = a * m + (1f - a) * r;
		}
		return x;
	}

	float getZ(float zCorrect) {
		float z;
		if (zCorrect > lev1 && zCorrect <= lev2) {
			float a = (zCorrect - lev1) / (lev2 - lev1);
			z = a * l2 + (1f - a) * l1;
		} else {
			float a = (lev3 - zCorrect) / (lev3 - lev2);
			z = a * l2 + (1f - a) * l3;
		}
		return z;
	}

	float dtToAngle(float dt) {
		return 360f*(dt/(PSOC_CLK*T)); 
	}

	/*
	// system of non-linear equations for unknown range variables
	float eq(float ra, float rb, float cos, float len) {
		return ra*ra + rb*rb - 2*ra*rb*cos - len*len;
	}

	// jacobian matrix
	Matrix<float> jacobian(float r0, float r1, float r2, float cos_01, float cos_12, float cos_02) {
		float[,] arr = {
			{ 2*r0 - 2*r1*cos_01, 2*r1 - 2*r0*cos_01, 0 },
			{ 0, 2*r1 - 2*r2*cos_12, 2*r2 - 2*r1*cos_12 },
			{ 2*r0 - 2*r2 * cos_02, 0, 2*r2 - 2*r0*cos_02 }
		};
		return DenseMatrix.OfArray(arr);
	}

	Vector<Single> triangulatePosition(float[] beta, float[] theta) {
		//angles between sensors 0, 1, 2
		float sb0 = (float) Math.Sin((double) beta[0]);
		float sb1 = (float) Math.Sin((double) beta[1]);
		float sb2 = (float) Math.Sin((double) beta[2]);

		float st0 = (float) Math.Sin((double) theta[0]);
		float st1 = (float) Math.Sin((double) theta[1]);
		float st2 = (float) Math.Sin((double) theta[2]);

		float cb0 = (float) Math.Cos((double) beta[0]);
		float cb1 = (float) Math.Cos((double) beta[1]);
		float cb2 = (float) Math.Cos((double) beta[2]);

		float ct0 = (float) Math.Cos((double) theta[0]);
		float ct1 = (float) Math.Cos((double) theta[1]);
		float ct2 = (float) Math.Cos((double) theta[2]);

		float cos_01 = sb0*ct0*sb1*ct1 + sb0*st0*sb1*st1 + cb0*cb1;
		float cos_12 = sb1*ct1*sb2*ct2 + sb1*st1*sb2*st2 + cb1*cb2;
		float cos_02 = sb0*ct0*sb2*ct2 + sb0*st0*sb2*st2 + cb0*cb2;
		//Debug.Log ("cos_01 = " + cos_01);
		//Debug.Log ("cos_12 = " + cos_12);
		//Debug.Log ("cos_02 = " + cos_02);

		float[] rand = { (float) UnityEngine.Random.Range (0.0f, 1.0f)*100f, (float) UnityEngine.Random.Range (0.0f, 1.0f)*100f, (float) UnityEngine.Random.Range (0.0f, 1.0f)*100f };

		Vector<Single> R = new DenseVector(rand);
		float[] eqs = { eq (R.At (0), R.At (1), cos_01, len_01), eq (R.At (1), R.At (2), cos_12, len_12), eq (R.At (0), R.At (2), cos_02, len_02) };

		// Newtonian Root Finding
		Vector<Single> M = new DenseVector(eqs);
		while(M.At(0) > 0.1 && M.At(1) > 0.1 && M.At(2) > 0.1) {
			eqs [0] = eq (R.At (0), R.At (1), cos_01, len_01);
			eqs [1] = eq (R.At (1), R.At (2), cos_12, len_12);
			eqs [2] = eq (R.At (0), R.At (2), cos_02, len_02);

			M = new DenseVector(eqs);
			R = R.Subtract(jacobian(R.At(0), R.At(1), R.At(2), cos_01, cos_12, cos_02).Inverse().Multiply(M));
		}
		return R;
	}

	// calculate and set car position
	void calculatePosition() {
		Vector<Single> ranges = triangulatePosition (beta, theta);

		float R_fromLighthouse = (float)(ranges.At (0) + ranges.At (1)) / 2;
		if (R_fromLighthouse < 0) {
			Debug.Log ("car distance less than 0");
			transform.SetPositionAndRotation (lastPos, transform.rotation);
			return;
		}

		float R;
		if (R_fromLighthouse > lighthouse_height) {
			R = (float)Math.Sqrt (R_fromLighthouse * R_fromLighthouse - lighthouse_height * lighthouse_height);
		} else {
			R = (float)Math.Sqrt (lighthouse_height * lighthouse_height - R_fromLighthouse * R_fromLighthouse);
		}

		// calculate cartesian position, reject if change too big
		float angle = (beta [0] + beta [1]) / 2;
		float angle2 = theta [0];
		float x = R_fromLighthouse * ((float)Math.Cos (angle))*IN_TO_M;
		if (Math.Abs (x) > prevX + CAR_BOUND) {
			return;
		}

		float y = R_fromLighthouse * ((float)Math.Sin (angle))*IN_TO_M;
		if (Math.Abs (y) > prevY + CAR_BOUND) {
			return;
		}

		prevX = Math.Abs (x);
		prevY = Math.Abs (y);

		//Debug.Log ("fromLighthouse = " + R_fromLighthouse);
		//Debug.Log ("fromOrigin = " + R_fromGlobalOrigin);
		Debug.Log ("angle = " + angle2 * (180 / Math.PI));
		//Debug.Log ("angle= " + Math.Cos (angle));
		//Debug.Log ("angle= " + Math.Sin (angle));
		//Debug.Log ("front/back = " + x);
		//Debug.Log ("left/right = " + y);
		set first calculated position as global 0
		if (firstUpdate) {
			firstY = y;
			globalOffset.Set (x, box_height, y);
			firstUpdate = false;
		}

		Vector3 curPos = transform.position;
		Quaternion curOrient = transform.rotation;

		Vector3 newPos = new Vector3 ();
		// Unity Coordinate System: {right: x, up: y, back: z}
		newPos.Set (y, box_height, x);
		//newPos.Set (x - globalOffset.x, globalOffset.y, y - globalOffset.z);

		transform.SetPositionAndRotation (newPos, curOrient);
		lastPos.Set (y, 0f, x);

		beta = new float[4];
		theta = new float[4];
		return;
	}*/
}
