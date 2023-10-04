///using Mono.Cecil;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.AI;
//using UnityEngine.XR;

/***********************************************
 * Filename:  		Player.cs
 * Date:      		05/16/2023
 * Mod. Date: 		05/26/2023
 * Mod. Initials:	JC
 * Author:    		James Clarke
 ************************************************/
public class CustomerWalk : MonoBehaviour
{
    #region Variables

    #region Serialized
    //Serialized
    [SerializeField] Animator m_animCustomer;
    [SerializeField] GameObject m_goTargetSet;
    [SerializeField] GameObject m_goPointObj;
    [SerializeField] Vector3 m_goSpawnObj;
    //[SerializeField] float m_fDetectRange = 3.5f;
    //[SerializeField] Transform m_tfStartPos;
    #endregion

    #region Public
    //Public
    public bool g_bWaitMode;
    public bool g_bSetTimer;
    public bool g_bWarned = false;
    public float m_fOrdertimerLimit = 60;
    #endregion

    #region Private
    //Private
    NavMeshAgent m_nmaNavTool;
    //bool m_bStartTimer;
    #endregion

    #region Math
    //Math
    float timer = 0;
    [SerializeField] float timerLimit = 0;
    int m_nRemoveCnt = 0;
    float m_fOrdertimer = 0;
    Vector3 m_vec3HeightVector;
    Vector3 m_vec3LaunchVec;
    Ray m_rLineCheck;
    GameObject m_goTempObject;
    #endregion

    #region Class Standard
    //Class Standard
    Transform m_tfEndPos;
    [SerializeField] List<GameObject> m_lTrashItems = new List<GameObject>();
    public AudioSource m_asSFX;
    public AudioClip m_acWarning;
    #endregion

    #region Class Custom
    //Class Custom
    Spawning m_spaSpawn;
    Customer m_cstPerson;
    LinePoints m_lpPoint;
    QueuePoints m_qpPoint;
    #endregion

    #endregion

    private void Awake()
    {
        m_nmaNavTool = GetComponent<NavMeshAgent>();
        m_animCustomer = GetComponent<Animator>();
        m_cstPerson = GetComponent<Customer>();
        m_goTargetSet = GameObject.Find("CustomerSystem");
        m_goPointObj = GameObject.Find("QueuePoint");

        m_lpPoint = m_goPointObj.GetComponent<LinePoints>();
        m_qpPoint = GameObject.Find("Customer System").transform.GetChild(0).GetComponent<QueuePoints>();
        m_spaSpawn = GameObject.Find("CustomerSingleton").GetComponent<Spawning>();
        if (m_goTargetSet == null)
        {
            m_goTargetSet = m_spaSpawn.g_goAssignTarget;
        }
        m_goSpawnObj = m_spaSpawn.g_vec3SpawnPosition;

        m_vec3HeightVector = new Vector3(0, gameObject.GetComponent<CharacterController>().height, 0);
        m_rLineCheck = new Ray(transform.position + m_vec3HeightVector / 2, transform.forward);

        int rand = Random.Range(0, m_lTrashItems.Count);
        m_goTempObject = m_lTrashItems[rand];
    }

    // Update is called once per frame
    void Update()
    {
        if (GameManager.g_Instance.g_bShiftActive == true)
        {
            if (m_lpPoint.g_lSavePoint.Count != 0)
            {
                if (!g_bWaitMode)
                {
                    if (m_cstPerson.g_bGotOrder == true)
                    {
                        BackToSpawn();
                    }

                    //Moves customer to queuing node
                    if (m_nmaNavTool.destination.x == transform.position.x && m_nmaNavTool.destination.z == transform.position.z)
                    {
                        if (m_nmaNavTool.enabled)
                        {
                            m_nmaNavTool.isStopped = false;

                            m_nmaNavTool.SetDestination(m_goPointObj.transform.position);
                        }
                    }
                }
                else
                {
                    //Starts timer for Customers to throw trash
                    if (g_bSetTimer)
                    {
                        m_fOrdertimer += Time.deltaTime;
                    }

                    //if timer hits limit and GotOrder is false, throw trash
                    if (m_cstPerson.g_bGotOrder == true)
                    {
                        if (transform.position.x == m_goSpawnObj.x && transform.position.z == m_goSpawnObj.z)
                        {
                            gameObject.SetActive(false);
                            transform.position = m_goSpawnObj;
                        }

                        BackToSpawn();
                        MoveUp();
                    }
                    else
                    {
                        if ((int)m_fOrdertimer == m_fOrdertimerLimit * 0.5f && GameManager.g_Instance.g_eCurrentDay != GameManager.g_eDays.Monday && !g_bWarned)
                        {
                            g_bWarned = true;
                            m_asSFX.clip = m_acWarning;
                            m_asSFX.Play();
                        }
                        if ((int)m_fOrdertimer == m_fOrdertimerLimit && GameManager.g_Instance.g_eCurrentDay != GameManager.g_eDays.Monday)
                        {
                            m_cstPerson.g_bGotOrder = true;
                            m_fOrdertimer = 0;

                            //create and throw trash, then leave
                            m_goTempObject.transform.position = new Vector3(transform.position.x, gameObject.GetComponent<CharacterController>().height / 1.1f, transform.position.z + .5f);
                            Instantiate(m_goTempObject);

                            RestaurantManager.g_Instance.MessUp();
                            if (RestaurantManager.g_Instance.m_nRatCount == 0)
                            {
                                RestaurantManager.g_Instance.RatUp();
                            }
                        }
                    }
                }
            }
        }
        else
        {
            BackToSpawn();
        }

        //Animates the customer
        if (m_nmaNavTool.velocity != Vector3.zero)
        {
            m_animCustomer.SetBool("IsMoving", true);

            if (m_nmaNavTool.velocity.z != 0)
            {
                m_animCustomer.SetFloat("Speed", .5f);
            }
        }
        else
        {
            m_animCustomer.SetBool("IsMoving", false);
        }
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Door"))
        {
            other.GetComponent<DoorOpen>().Interact();
        }

        if (other.gameObject == m_lpPoint.g_lSavePoint[0].gameObject)
        {
            m_nmaNavTool.isStopped = true;
        }
    }

    private void BackToSpawn()
    {
        if (m_nRemoveCnt < 1)
        {
            m_nRemoveCnt++;
            m_lpPoint.g_lSaveCustomer.Remove(gameObject);
            m_spaSpawn.m_nCusCount--;
        }
        if (transform.position.x != m_goSpawnObj.x && transform.position.z != m_goSpawnObj.z)
        {
            gameObject.GetComponent<BoxCollider>().enabled = false;
            if (m_nmaNavTool.enabled)
            {

                m_nmaNavTool.isStopped = false;
                m_nmaNavTool.SetDestination(m_goSpawnObj);
                //m_bStartTimer = false;
            }
        }
        else
        {
            gameObject.SetActive(false);
            transform.position = m_goSpawnObj;
            m_nRemoveCnt = 0;
        }
    }

    private void MoveUp()
    {
        timer += Time.deltaTime;
        int nStop = 0;
        for (int i = 0; i < m_lpPoint.g_lSavePoint.Count; i++)
        {
            if (i == 0 && nStop > 1)
            {
                m_lpPoint.g_lSavePoint[i].SetActive(false);
                nStop++;
            }

            if ((int)timer == timerLimit)
            {
                timer = 0;
                m_lpPoint.g_lSavePoint[i].SetActive(true);
            }
        }

        for (int i = 0; i < m_lpPoint.g_lSaveCustomer.Count; i++)
        {
            if (m_lpPoint.g_lSaveCustomer[i].GetComponent<NavMeshAgent>().isStopped == true)
            {
                m_lpPoint.g_lSaveCustomer[i].transform.position = Vector3.Lerp(m_lpPoint.g_lSaveCustomer[i].transform.position, m_lpPoint.g_lSavePoint[i].transform.position, Time.deltaTime);
            }
        }
    }
}

