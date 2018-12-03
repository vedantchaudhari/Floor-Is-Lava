using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LavaController : MonoBehaviour
{

    public int NumLivingPlayers;
    GameObject[] playerList;

    float[] LavaHeights = { -16f, -13.95f, -12.73f, -11.25f, -10.23f };
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
        print(NumLivingPlayers);
        print(playerList.Length);
        print(LavaHeights.Length);
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if (gameObject.transform.position.y <= LavaHeights[LavaHeights.Length - NumLivingPlayers])
            gameObject.transform.SetPositionAndRotation(new Vector3(gameObject.transform.position.x, gameObject.transform.position.y + 0.005f, gameObject.transform.position.z), gameObject.transform.rotation);
        print(NumLivingPlayers);
        print(LavaHeights.Length);
    }


    void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "NonLava")
        {
            Physics.IgnoreCollision(gameObject.GetComponent<Collider>(), collision.gameObject.GetComponent<Collider>(), true);
        }
    }
}
