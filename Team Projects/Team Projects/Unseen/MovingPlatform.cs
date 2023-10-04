using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class MovingPlatform : MonoBehaviour
{
    [SerializeField] GameObject moveUpTo;
    [SerializeField] GameObject moveRightTo;
    [SerializeField] float speed;
    [SerializeField] bool isGoingUp;
    [SerializeField] bool isGoingRight;
    [SerializeField] bool switchMode;
    Vector3 origPos;

    void Awake()
    {
        origPos = transform.parent.position;
        //switchMode = true;
        //isGoingUp = true;
    }

    void FixedUpdate()
    {
        if (switchMode)
        {
            VerticalMode();
        }
        else
        {
            HorizontalMode();
        }
    }
    private float Checkfordistance(Vector3 _one, Vector3 _two)
    {
        float distance = Vector3.Distance(_one, _two);
        return distance;
    }
    void VerticalMode()
    {
        if (transform.parent.position != moveUpTo.transform.position && isGoingUp)
        {
            if (Checkfordistance(transform.parent.position, moveUpTo.transform.position) <= 0.05f)
            {
                isGoingUp = false;
            }
            else
            {
                transform.parent.position = Vector3.Lerp(transform.parent.position, moveUpTo.transform.position, Time.deltaTime * speed);
            }
        }
        if (transform.parent.position != origPos && !isGoingUp)
        {
            if (Checkfordistance(transform.parent.position, origPos) <= 0.05f)
            {
                isGoingUp = true;
            }
            else
            {
                transform.parent.position = Vector3.Lerp(transform.parent.position, origPos, Time.deltaTime * speed);
            }
        }
    }
    void HorizontalMode()
    {
        if (transform.parent.position != moveRightTo.transform.position && isGoingRight)
        {
            if (Checkfordistance(transform.parent.position, moveRightTo.transform.position) <= 0.05f)
            {
                isGoingRight = false;
            }
            else
            {
                transform.parent.position = Vector3.Lerp(transform.parent.position, moveRightTo.transform.position, Time.deltaTime * speed);
            }
        }
        if (transform.parent.position != origPos && !isGoingRight)
        {
            if (Checkfordistance(transform.parent.position, origPos) <= 0.05f)
            {
                isGoingRight = true;
            }
            else
            {
                transform.parent.position = Vector3.Lerp(transform.parent.position, origPos, Time.deltaTime * speed);
            }
        }
    }
}
