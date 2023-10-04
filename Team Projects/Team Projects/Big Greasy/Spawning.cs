using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using UnityEngine;
using UnityEngine.AI;

/***********************************************
 * Filename:  		Player.cs
 * Date:      		05/26/2023
 * Mod. Date: 		05/29/2023
 * Mod. Initials:	JC
 * Author:    		James Clarke
 ************************************************/
public class Spawning : MonoBehaviour
{
    [SerializeField] GameObject m_goCusSingle;
    [SerializeField] List<GameObject> m_goCusList;
    public GameObject g_goAssignTarget;


    public Vector3 g_vec3SpawnPosition;

    LinePoints m_lpProxy;
    [SerializeField] float m_ftime = 0;
    public float m_fTimeLimit = 5;

    int m_nSpawnCount = 0;
    //[SerializeField]
    public int m_nCusCount = 0;
    public int m_nCount = 0;

    [SerializeField]int nTargetChildCount = 0;

    public bool g_bCanSpawn = true;
    // Start is called before the first frame update

    private void Awake()
    {
        if (g_vec3SpawnPosition == Vector3.zero || g_vec3SpawnPosition == null)
            g_vec3SpawnPosition = GameObject.Find("CustomerSingleton").transform.position;

        for (int i = 0; i < transform.childCount; i++)
        {
            m_goCusList.Add(m_goCusSingle.transform.GetChild(i).gameObject);
        }

        if (g_goAssignTarget == null)
            g_goAssignTarget = GameObject.Find("Customer System");



        if (g_goAssignTarget == GameObject.Find("Customer System"))
        {
            nTargetChildCount = g_goAssignTarget.transform.childCount - 1;
        }
        else
        {
            nTargetChildCount = g_goAssignTarget.transform.childCount;
        }

    }
    
    // Update is called once per frame
    void Update()
    {
        m_ftime += Time.deltaTime;
        if (GameManager.g_Instance.g_bShiftActive == true)
        {
            for (; m_nSpawnCount < 1; m_nSpawnCount++)
            {
                if (m_nCusCount == nTargetChildCount)
                {
                    g_bCanSpawn = false;
                    break;
                }
                else
                {
                    g_bCanSpawn = true;
                }

                //if (g_bCanSpawn)
                //{
                //spawning
                int rand = Random.Range(0, m_goCusList.Count);
                if (m_goCusList[rand] != null && m_goCusList[rand].activeSelf == false)
                {
                    m_goCusList[rand].transform.rotation = Quaternion.identity;
                    m_goCusList[rand].gameObject.SetActive(true);
                    m_goCusList[rand].gameObject.GetComponent<CharacterController>().detectCollisions = true;
                    m_goCusList[rand].gameObject.GetComponent<BoxCollider>().enabled = true;

                    m_nCusCount++;
                    m_ftime = 0;
                }
                //}
            }

            if (m_ftime >= m_fTimeLimit && g_bCanSpawn == true)//m_nCusCount < 1
            {
                //m_nCount = 0;
                m_nSpawnCount = 0;
            }

        }
    }
}
