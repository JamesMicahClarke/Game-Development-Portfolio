using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Lift : MonoBehaviour
{
    [SerializeField] GameObject moveelevatorto;
    [SerializeField] GameObject step;
    [SerializeField] GameObject blockers;
    [SerializeField] bool MoveUp;
    [SerializeField] bool autoSwitch;
    [SerializeField] bool isAuto;
    [SerializeField] float speed;
    CharacterController cc;
    [SerializeField] bool inElevatorRange;
    Vector3 OG_Elevator_Pos;
    private void Start()
    {
        OG_Elevator_Pos = transform.parent.position;
        blockers.SetActive(false);

    }
    private void Update()
    {
        if (inElevatorRange && GameManager.instance.playerScript.haselevatorkey)
        {
            if (GameManager.instance.gameOver.activeInHierarchy == false && (Input.GetKeyDown(KeyCode.Z) || Input.GetKeyDown(KeyCode.E)))
            {
                if (transform.parent.position != moveelevatorto.transform.position)
                {
                    MoveUp = true;
                }
                else if (transform.parent.position != OG_Elevator_Pos)
                {
                    MoveUp = false;
                }
            }
        }

        if (isAuto == true)
        {
            AutoMode(autoSwitch);
        }

        if (MoveUp)
        {
            MoveElevatorUp();
        }
        if (!MoveUp)
        {
            MoveElevatorDown();
        }

    }

    private void MoveElevatorUp()
    {
        if (Checkfordistance(transform.parent.position, moveelevatorto.transform.position) <= 0.05f)
        {
            transform.parent.position = moveelevatorto.transform.position;
        }
        if (transform.parent.position != moveelevatorto.transform.position)
        {
            transform.parent.position = Vector3.Lerp(transform.parent.position, moveelevatorto.transform.position, Time.deltaTime * speed);
            step.SetActive(false);
            blockers.SetActive(true);
        }
        else
        {
            step.SetActive(true);
            blockers.SetActive(false);
        }

    }
    private void MoveElevatorDown()
    {
        if (Checkfordistance(transform.parent.position, OG_Elevator_Pos) <= 0.05)
        {
            transform.parent.position = OG_Elevator_Pos;
        }
        if (transform.parent.position != OG_Elevator_Pos)
        {
            transform.parent.position = Vector3.Lerp(transform.parent.position, OG_Elevator_Pos, Time.deltaTime * speed);
            step.SetActive(false);
            blockers.SetActive(true);
        }
        else
        {
            step.SetActive(true);
            blockers.SetActive(false);
        }
    }

    private float Checkfordistance(Vector3 _one, Vector3 _two)
    {
        float distance = Vector3.Distance(_one, _two);
        return distance;
    }

    void AutoMode(bool auto)
    {

        if (moveelevatorto.activeSelf == true && auto == true)
        {
            if (transform.parent.position != moveelevatorto.transform.position)
            {
                MoveUp = true;
            }
            else
            {
                moveelevatorto.SetActive(false);
            }
        }
        else
        {

            MoveUp = false;

            if (transform.parent.position == OG_Elevator_Pos)
                moveelevatorto.SetActive(true);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            inElevatorRange = true;
            cc = other.GetComponent<CharacterController>();

        }
    }

    private void OnTriggerExit(Collider other)
    {
        if (other.CompareTag("Player"))
        {
            inElevatorRange = false;
        }
    }
}