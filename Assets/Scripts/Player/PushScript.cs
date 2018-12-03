using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PushScript : MonoBehaviour
{
    Vector3 PushDir;
    public float pushForce = 600;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {

    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.GetComponent<Rigidbody>() != null)
        {
            PushDir = gameObject.transform.root.forward;
            other.gameObject.GetComponent<Rigidbody>().AddForce(PushDir.normalized * pushForce);
        }
    }
}
