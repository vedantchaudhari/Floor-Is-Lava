using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LavaController : MonoBehaviour
{

    public int NumLivingPlayers;
    GameObject[] playerList;

    float[] LavaHeights = { -13.95f, -11.75f, -10.23f };
     // Use this for initialization
    void Start()
    {
        Physics.IgnoreLayerCollision(4, 9);
        playerList = GameObject.FindGameObjectsWithTag("Player");
        NumLivingPlayers = 0;
       foreach(GameObject player in playerList)
        {
            player.GetComponent<PlayerController>().setPlayerNum(NumLivingPlayers);
            NumLivingPlayers++;
        }
      //  print(NumLivingPlayers);
     //   print(playerList.Length);
      //  print(LavaHeights.Length);
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (NumLivingPlayers > 1)
        {
            if (gameObject.transform.position.y <= LavaHeights[LavaHeights.Length - (NumLivingPlayers-1)])
                gameObject.transform.SetPositionAndRotation(new Vector3(gameObject.transform.position.x, gameObject.transform.position.y + 0.0015f, gameObject.transform.position.z), gameObject.transform.rotation);

        }
      //  print(NumLivingPlayers);
      //  print(LavaHeights.Length);
    }


    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "NonLava")
        {
            Physics.IgnoreCollision(gameObject.GetComponent<Collider>(), collision.gameObject.GetComponent<Collider>(), true);
        }
    }
}
