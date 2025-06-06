using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParalysisGas : MonoBehaviour
{
    GameObject paralysisGas;
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
        if (paralysisGas.activeSelf == true)
        {
            GameManager.instance.playerScript.controllable = false;
            GameManager.instance.ShowParalysis();
        }
    }
    private void OnTriggerExit(Collider other)
    {
        GameManager.instance.HideParalysis();
    }
}
