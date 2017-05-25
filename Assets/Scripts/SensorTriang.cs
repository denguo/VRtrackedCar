using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;
using System;
using MathNet.Numerics;
using MathNet.Numerics.LinearAlgebra;
using MathNet.Numerics.LinearAlgebra.Single;

public class SensorTriang : MonoBehaviour {
	public const string COM_NUMBER = "COM7";
	public const int BAUDRATE = 38400;
	public const int PSOC_CLK = 24000;
	public const float T = 8.33f;

	public const float IN_TO_M = 0.0254f;
	public const int N_SENSORS = 4;
	public const float box_height = 0.15f;
	public const float lighthouse_height = 41f;
	public const int S_CHARACTER = 115;
	public const int DT_BOUND = 150000;
	public const float CAR_BOUND = 0.5f;

	static SerialPort sp = new SerialPort(COM_NUMBER, BAUDRATE);

	private float[] beta = new float[4];
	private float[] theta = new float[4];

	private float len_01 = 8.7f;
	private float len_12 = 6.75f;
	private float len_02 = 6.9f;

	private bool firstUpdate = true;
	private Vector3 globalOffset = new Vector3();
	private float prevX = float.PositiveInfinity;
	private float prevY = float.PositiveInfinity;
	private float firstY = 0f;
	private Vector3 lastPos = new Vector3 ();

	private Vector2 lp = new Vector2();
	private bool firstRot;

	private float[] xavg = new float[10];
	private float[] yavg = new float[10];

	private float[] r0avg = new float[10];
	private float[] r1avg = new float[10];

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
		sp.ReadTimeout = 50;

		lastPos.Set (0f, 0f, 0f);
		lp.Set (-1f, 1f);
		firstRot = true;

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
				//if (sp.BytesToRead == null) return;
				while (true) {
					while (Convert.ToInt32 (sp.ReadByte ()) != S_CHARACTER) {
					}
					//Debug.Log ("s found");

					int id = sp.ReadByte ();
					int axis = sp.ReadByte ();
					int dt = (sp.ReadByte () << 0) + (sp.ReadByte () << 8) + (sp.ReadByte () << 16);

					if (axis == 0) {        // x sweep
						//Debug.Log(dt);
						//Debug.Log("id= " + id + " dt= " + dt);
						beta [id] = dtToAngle (dt); 
						//Debug.Log ("id = " + id + " axis= " + axis + " dx: " + dt);
					} else {   // y sweep
						//Debug.Log("id= " + id + " dt= " + dt);
						theta [id] = dtToAngle (dt); 
						//Debug.Log ("id = " + id + " axis= " + axis + " dy: " + dt);
					}

					int S = sp.ReadByte();
					id = sp.ReadByte ();
					axis = sp.ReadByte ();
					dt = (sp.ReadByte () << 0) + (sp.ReadByte () << 8) + (sp.ReadByte () << 16);

					if (axis == 0) {        // x sweep
						//Debug.Log(dt);
						//Debug.Log("id= " + id + " dt= " + dt);
						beta [id] = dtToAngle (dt); 
						//Debug.Log ("id = " + id + " axis= " + axis + " dx: " + dt);
					} else {   // y sweep
						//Debug.Log("id= " + id + " dt= " + dt);
						theta [id] = dtToAngle (dt); 
						//Debug.Log ("id = " + id + " axis= " + axis + " dy: " + dt);
					}

					S = sp.ReadByte();
					id = sp.ReadByte ();
					axis = sp.ReadByte ();
					dt = (sp.ReadByte () << 0) + (sp.ReadByte () << 8) + (sp.ReadByte () << 16);

					if (axis == 0) {        // x sweep
						//Debug.Log(dt);
						//Debug.Log("id= " + id + " dt= " + dt);
						beta [id] = dtToAngle (dt); 
						//Debug.Log ("id = " + id + " axis= " + axis + " dx: " + dt);
					} else {   // y sweep
						//Debug.Log("id= " + id + " dt= " + dt);
						theta [id] = dtToAngle (dt); 
						//Debug.Log ("id = " + id + " axis= " + axis + " dy: " + dt);
					}


					// read values until buffer is full and positions are calculated
					if (bufferFull ()) {
						calculatePosition ();
						return;
					}
				}
			} catch (System.Exception) {
				//  throw;
			}
		} else {
			Debug.Log ("port not open on update");
		}
	}

	float dtToAngle(float dt) {
		return (((float)Math.PI)/180f)*360f*(dt/(PSOC_CLK*T)); 
	}

	bool bufferFull() {
		
		for (int i = 0; i < 3; i++) {
			if (beta[i] <= 0 || theta [i] <= 0) {
				return false;
			}
		}
		return true;

		/*
		if (beta [0] != 0 && theta [0] != 0 && beta [1] != 0 && theta [1] != 0) {
			getThirdAngle (0, 1, beta [0], theta [0], beta [1], theta [1]);
		}
		else if (beta [1] != 0 && theta [1] != 0 && beta [2] != 0 && theta [2] != 0) {
			getThirdAngle (1, 2, beta [1], theta [1], beta [2], theta [2]);
		}*/
	}

	float[] toAngleRadians(float[] dt) {
		float[] angles = new float[dt.Length];
		for (int i = 0; i < dt.Length; i++) {
			angles[i] = ((float)Math.PI/180f)*360f*(dt[i]/T);
		}
		//Debug.Log ("angles");
		//Debug.Log (angles[0]);
		//Debug.Log (angles[1]);
		//Debug.Log (angles[2]);
		return angles;
	}

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

	Vector2 polarToCartesian(float R, float beta) {
		float x = R * (float)Math.Cos(beta);
		float y = R * (float)Math.Sin(beta);
		Vector2 v = new Vector2();
		v.Set(x, y);
		return v;
	}
	// calculate and set car position
	void calculatePosition() {
		Vector<Single> ranges = triangulatePosition (beta, theta);

		float r0new = ranges.At (0);
		float r1new = ranges.At (1);

		r0avg = updateAvg (r0avg, r0new);
		r1avg = updateAvg (r1avg, r1new);

		Vector2 v0 = polarToCartesian (getAvg(r0avg), beta [0]);
		Vector2 v1 = polarToCartesian (getAvg(r1avg), beta [1]);
		Vector2 l = v1 - v0;
		if (firstRot) {
			lp = l;
			firstRot = false;
		} else {
			// orientation
			l.Normalize ();
			lp.Normalize ();
			float cos_ang = Vector2.Dot (l, lp);
			//Debug.Log ("cos_ang" + cos_ang);
			float ang = (180f / (float)Math.PI)*((float)Math.Acos (cos_ang));
			//Debug.Log ("y rotation= " + ang);
			lp = l;

			Vector3 rot = new Vector3 ();
			if ( Math.Abs(ang) > 0) {
				rot.Set (0f, ang, 0f);
			}
			transform.Rotate (rot);
		}

		// position
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
		//Debug.Log ("angle = " + angle2 * (180 / Math.PI));
		//Debug.Log ("angle= " + Math.Cos (angle));
		//Debug.Log ("angle= " + Math.Sin (angle));
		//Debug.Log ("front/back = " + x);
		//Debug.Log ("left/right = " + y);
		/* set first calculated position as global 0
			if (firstUpdate) {
				firstY = y;
				globalOffset.Set (x, box_height, y);
				firstUpdate = false;
			}*/

		Vector3 curPos = transform.position;
		Quaternion curOrient = transform.rotation;

		Vector3 newPos = new Vector3 ();
		// Unity Coordinate System: {right: x, up: y, back: z}
		newPos.Set (getAvg(yavg), box_height, getAvg(xavg));
		//newPos.Set (x - globalOffset.x, globalOffset.y, y - globalOffset.z);

		transform.SetPositionAndRotation (newPos, curOrient);
		lastPos.Set (getAvg(yavg), 0f, getAvg(xavg));

		xavg = updateAvg (xavg, x);
		yavg = updateAvg (yavg, y);

		beta = new float[4];
		theta = new float[4];
		return;
	}

	float[] updateAvg(float[] a, float newval) {
		for (int i = a.Length - 1; i >= 1; i--) {
			a [i] = a [i - 1];
		}
		a [0] = newval;
		return a;
	}

	float getAvg(float[] arr) {
		float sum = 0f;
		for (int i = 0; i < arr.Length; i++) {
			sum += arr [i];
		}
		return sum / arr.Length;
	}

	void getThirdAngle(int ida, int idb, float ba, float ta, float bb, float tb) {
		float bc;
		float tc;
		if (ida == 0 && idb == 1) {
			bc = (ba + bb) / 2;
			tc = ta - ((ba - bb) / 2);
			beta [2] = bc;
			theta [2] = tc;
		}
		else if (ida == 1 && idb == 2) {
			bc = bb + (bb - ba);
			tc = ta;
			beta [0] = bc;
			theta [0] = tc;
		}
		else {
			bc = bb - (ba - bb);
			tc = ta;
			beta [1] = bc;
			theta [1] = tc;
		}
	}
}
