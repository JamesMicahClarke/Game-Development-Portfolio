using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Paralysis : MonoBehaviour
{
    private bool playerInTrigger;
    [SerializeField] ParticleSystem gas;
    [SerializeField] bool playquestionmark;
    [SerializeField] BoxCollider stop;
    private FlashingEffect fe;

    void Start()
    {
        fe = GameManager.instance.player.GetComponentInChildren<FlashingEffect>();
        playquestionmark = true;
    }
    void Update()
    {
        if (stop.enabled == false)
        {
            //GameManager.instance.playerScript.Paralysis(false);
            BlinkOff();
            GameManager.instance.HideParalysis();
            playerInTrigger = false;
        }
        if (playerInTrigger)
        {
            GameManager.instance.playerScript.FallingDown();
            GameManager.instance.playerScript.BecomeVisible();
           
        }
        if (playquestionmark)
        {
            //Debug.Log("Running");
            gas.Play();

            playquestionmark = false;
            StartCoroutine(Delay());
        }

    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            //GameManager.instance.playerScript.Paralysis(true);

            StartCoroutine(ParalysisDelay());
            GameManager.instance.ShowParalysis();

        }

    }
    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            playerInTrigger = false;
            GameManager.instance.playerScript.Paralysis(false);
            BlinkOff();
            GameManager.instance.HideParalysis();

        }

    }

    IEnumerator Delay()
    {
        StartCoroutine(BoxDelay());
        yield return new WaitForSeconds(9);
        playquestionmark = true;
    }
    IEnumerator BoxDelay()
    {
        stop.enabled = true;
        yield return new WaitForSeconds(4.5f);
        stop.enabled = false;
        GameManager.instance.playerScript.Paralysis(false);
        GameManager.instance.invisBar.RegenBar();
    }
    IEnumerator ParalysisDelay()
    {
        yield return new WaitForSeconds(0.3f);
        playerInTrigger = true;
        GameManager.instance.playerScript.Paralysis(true);
        BlinkOn(Color.yellow, Color.white, 3f);
    }

    private void BlinkOn(Color _color1, Color _color2, float _blinkSpeed)
    {
        fe.FlashingColor1 = _color1;
        fe.FlashingColor2 = _color2;
        /*
        if (fe.FlashingColor1 == Color.white)
        {
            fe.FlashingColor1 = _color1;
            fe.FlashingColor2 = _color2;
        }
        else
        {
            fe.FlashingColor2 = _color1;
        }*/
        fe.Speed = _blinkSpeed;
        fe.enabled = true;
    }
    private void BlinkOff()
    {
        fe.FlashingColor1 = Color.white;
        fe.FlashingColor2 = Color.white;
        /*
        if (fe.FlashingColor2 == Color.white)
        {
            fe.FlashingColor1 = Color.white;
            fe.FlashingColor2 = Color.white;
        }
        else
        {
            fe.FlashingColor2 = Color.white;
        }*/
        //GameManager.instance.playerScript.SetPlayerMaterial(GameManager.instance.playerScript.GetPlayerMaterial());
        fe.enabled = false;
    }
}
