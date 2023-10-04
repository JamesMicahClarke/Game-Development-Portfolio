using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class VentAccess : MonoBehaviour
{
    [SerializeField] GameObject bars;
    [SerializeField] bool isTop;
    [SerializeField] bool isBottom;

    private void OnTriggerStay(Collider other)
    {
        if (isTop)
        {
            TopTrigger();
        }
        if(isBottom)
        {
            BottomTrigger();
        }
    }
    private void OnTriggerExit(Collider other)
    {
        bars.SetActive(true);
        
    }

    void TopTrigger()
    {
        if (Input.GetKey(KeyCode.Z) || Input.GetKey(KeyCode.E))
        {
            bars.SetActive(false);
            isTop = true;
        }
    }
    void BottomTrigger()
    {
        bars.SetActive(false);
        isBottom = true;
    }
}
