using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ReflectionProbeWindow : MonoBehaviour
{
    public ReflectionProbe windowProbe;

    // Start is called before the first frame update
    void Start()
    {
       // gameObject.GetComponent<MeshRenderer>().probeAnchor = windowProbe.transform;
     //   gameObject.GetComponent<MeshRenderer>().material = windowProbe.GetComponent<Renderer>().material;
       // gameObject.GetComponent<Material>().SetTexture("Window",windowProbe.texture);
    }

    // Update is called once per frame
    void Update()
    {
        
    }
}
