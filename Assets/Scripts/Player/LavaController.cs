using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LavaController: MonoBehaviour {

    int ticker = 0;
	// Use this for initialization
	void Start () {
		
	}
	
	// Update is called once per frame
	void FixedUpdate () {
        ticker++;
        if (ticker%10 == 0)
            gameObject.transform.SetPositionAndRotation(new Vector3(gameObject.transform.position.x, gameObject.transform.position.y +  0.02f, gameObject.transform.position.z),gameObject.transform.rotation);
	}
}
