using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Experimental.GlobalIllumination;

public class Flashlight : MonoBehaviour
{

    GameObject m_goFlashlightHolder;
    [SerializeField] GameObject m_goLight;
    GameObject m_goFlashLight;
    GameObject m_goCamLight;
    GameObject m_goPlayer;
    [SerializeField] Light m_slLighting;
    public bool g_bAvailable;
    public bool g_bIsOn;
    bool m_bTurnOn = true;
    float m_fOffTimerA = 0;
    float m_fOnTimerA = 0;
    float m_fOffTimerB = 0;
    float m_fOnTimerB = 0;
    //[SerializeField] float m_fLightTimer = 0;
    [SerializeField] float m_fTimeLimit;
    [SerializeField] float m_fLightTimeLimit;
    //[SerializeField] float m_fSwitchCount = 0;
    [SerializeField] float m_fFlashDelayA;
    [SerializeField] float m_fFlashDelayB;
    [SerializeField] float m_fCastRange = 0.001f;
    [SerializeField] float m_fSpeedModCam = 1;
    [SerializeField] float m_fSpeedModFlash = 1;

    [SerializeField] float m_fCamIntensity = 5;
    [SerializeField] float m_fFlashIntensity = 10;

    private void Awake()
    {
        m_goPlayer = Camera.main.transform.parent.gameObject;
        m_goFlashLight = GameObject.Find("Low Light");
        for (int i = 0; i < Camera.main.transform.childCount; i++)
        {
            if (Camera.main.transform.GetChild(i).name == "Camera Light")
            {
                m_goCamLight = Camera.main.transform.GetChild(i).gameObject;

            }
        }
        m_goFlashlightHolder = transform.GetChild(0).gameObject;
        m_goLight = m_goFlashLight;

    }
    private void Start()
    {
        g_bAvailable = GameManager.g_Instance.g_bFlashlight;
        if (g_bAvailable)
        {
            m_goFlashlightHolder.SetActive(true);
        }
        else
        {
            m_goFlashlightHolder.SetActive(false);
        }
    }
    // Update is called once per frame
    void Update()
    {

        m_slLighting = m_goLight.GetComponent<Light>();
        //m_fLightTimer += Time.deltaTime;
        //if (m_fLightTimer > m_fLightTimeLimit)
        //{
        //    m_fSwitchCount++;
        //}
        //if (m_fSwitchCount == 1)
        //{
        if (m_slLighting.intensity < m_fCamIntensity && m_goLight == m_goCamLight)
        {
            m_slLighting.intensity += m_fSpeedModCam * Time.deltaTime;

            //if (m_slLighting.intensity == m_fCamIntensity)
            //{
            //    m_fLightTimer = 0;
            //    m_fSwitchCount = 0;
            //}
        }
        else if (m_slLighting.intensity < m_fFlashIntensity && m_goLight == m_goFlashLight)
        {
            m_slLighting.intensity += m_fSpeedModFlash * Time.deltaTime;

            //if (m_slLighting.intensity == m_fCamIntensity)
            //{
            //    m_fLightTimer = 0;
            //    m_fSwitchCount = 0;
            //}
        }
        //}

        //close up light range
        if (g_bIsOn)
        {
            Ray rLightCast = new Ray(Camera.main.transform.position, Camera.main.transform.forward);
            Debug.DrawRay(rLightCast.origin, new Vector3(rLightCast.direction.x, rLightCast.direction.y, rLightCast.direction.z + m_fCastRange));
            if (Physics.Raycast(rLightCast, m_fCastRange) && (m_goFlashlightHolder.activeSelf == true || m_goCamLight.activeSelf == false))
            {
                m_goFlashlightHolder.SetActive(false);
                m_goLight = m_goCamLight;
                m_goLight.SetActive(true);


                m_slLighting.intensity = 0;

            }
            else if (!Physics.Raycast(rLightCast, m_fCastRange) && (m_goCamLight.activeSelf == true || m_goFlashlightHolder.activeSelf == false))
            {
                m_goFlashlightHolder.SetActive(true);
                if (m_goLight = m_goCamLight)
                {
                    m_goLight.SetActive(false);
                }
                m_goLight = m_goFlashLight;

                m_slLighting.intensity = 0;
            }
        }

        //flicker timer
        if (m_goFlashlightHolder.activeSelf == true || m_goCamLight.activeSelf == true)
        {

            m_fOffTimerA += Time.deltaTime;
            if (m_fOffTimerA > m_fTimeLimit)
            {
                m_fOnTimerA += Time.deltaTime;

                //flick off
                m_goLight.SetActive(false);
                //if timer b, then flick on
                if (m_fOnTimerA > m_fFlashDelayA)
                {
                    if (m_goLight == m_goCamLight)
                    {
                        m_slLighting.intensity = m_fCamIntensity;
                    }
                    m_goLight.SetActive(true);
                    m_fOffTimerA = 0;
                    m_fOnTimerA = 0;

                }
            }

            m_fOffTimerB += Time.deltaTime;

            if (m_fOffTimerB > m_fTimeLimit)
            {
                m_fOnTimerB += Time.deltaTime;
                m_goLight.SetActive(false);

                if (m_fOnTimerB > m_fFlashDelayB)
                {
                    m_goLight.SetActive(true);
                    m_fOffTimerB = 0;
                    m_fOnTimerB = 0;
                }
            }
        }

            if (Input.GetButtonDown("Flashlight") && GameManager.g_Instance.g_bFlashlight)
            {
                if (m_goFlashlightHolder.activeSelf == true || m_goCamLight.activeSelf == true)
                {
                    g_bIsOn = false;
                    m_goFlashlightHolder.SetActive(false);
                    if (m_goCamLight.activeSelf == true)
                    {
                        m_goCamLight.SetActive(false);
                    }
                }
                else if (m_goFlashlightHolder.activeSelf == false)
                {
                    g_bIsOn = true;
                    m_goFlashlightHolder.SetActive(true);
                    m_slLighting.intensity = 0;
                }
            }
        //}
    }
}
