using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HidingTable : MonoBehaviour
{
    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            GameManager.instance.playerScript.canCrouch = false;
            GameManager.instance.playerScript.reducedSpeed = false;
        }
    }

    private void OnTriggerExit(Collider other)
    {
        GameManager.instance.playerScript.canCrouch = true;
    }
}
