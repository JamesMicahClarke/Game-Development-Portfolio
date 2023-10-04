using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MovingStay : MonoBehaviour
{
    CharacterController cc;

    private void OnTriggerEnter(Collider other)
    {
        if(other.tag == "Player")
        {
            cc = other.GetComponent<CharacterController>();
            other.transform.SetParent(transform.parent);
        }
    }
    private void OnTriggerExit(Collider other)
    {
        if (other.tag == "Player")
        {
            other.transform.SetParent(null);
        }
    }
}
