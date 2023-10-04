using UnityEngine;
using UnityEngine.AI;

public class QueuePoints : MonoBehaviour
{
    LinePoints m_lpPoint;
    [SerializeField] GameObject m_goPointObj;
    CustomerWalk m_cwProxy;
    public Customer g_cCustomer;
    public bool g_bCanMoveUp;

    public float m_fTurnSpeed = 0;

    Collider m_colCustomer;
    private void Awake()
    {
        m_goPointObj = GameObject.Find("QueuePoint");
        m_lpPoint = m_goPointObj.GetComponent<LinePoints>();
         
    }
    private void OnTriggerEnter(Collider other)
    {
        if (other.CompareTag("Customer"))
        {
            m_cwProxy = other.GetComponent<CustomerWalk>();

            g_cCustomer = other.GetComponent<Customer>();
            if (m_lpPoint.g_lSavePoint[0] == gameObject)
            {
                g_cCustomer.Order();
                m_cwProxy.g_bSetTimer = true;
                m_cwProxy.m_asSFX = other.GetComponent<AudioSource>();
            }
            m_colCustomer = other;

            other.gameObject.GetComponent<NavMeshAgent>().isStopped = true;
            //other.gameObject.GetComponent<CharacterController>().detectCollisions = false;


            m_cwProxy.g_bWaitMode = true;

        }
    }

    private void FixedUpdate()
    {
        if (m_colCustomer != null)
        {

            m_colCustomer.transform.rotation = Quaternion.Lerp(m_colCustomer.transform.rotation, Quaternion.identity, m_fTurnSpeed * Time.deltaTime);
            //m_colCustomer.transform.position = Vector3.Lerp(m_colCustomer.transform.position, transform.position, Time.deltaTime);
        }
    }
}
