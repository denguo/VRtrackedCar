using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO.Ports;

public class MoveBox : MonoBehaviour {
	public float speed;

	private float amountToMove;

	static SerialPort sp = new SerialPort("COM7", 9600);

	// Use this for initialization
	void Start () {
		sp.Open();
		sp.ReadTimeout = 1;
	}
	
	// Update is called once per frame
	void Update () {
		//Debug.Log("test");
		amountToMove = speed * Time.deltaTime;

		if (sp.IsOpen) {
			try {
				MoveObject(sp.ReadByte());
				Debug.Log("test");
				Debug.Log("direction = " + sp.ReadByte().ToString());
			}
			catch (System.Exception) {
			}
		}
	}

	void MoveObject(int Direction) {
		if (Direction == 1) {
			transform.Translate(Vector3.left * amountToMove, Space.World);
		}
		if (Direction == 2) {
			transform.Translate(Vector3.right * amountToMove, Space.World);
		}
	}
}
