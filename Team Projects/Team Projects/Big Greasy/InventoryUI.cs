using System.Collections.Generic;
using TMPro;
using Unity.VisualScripting;
using UnityEngine;

public class InventoryUI : MonoBehaviour
{
    [SerializeField] float m_fTimer;
    //[SerializeField] float m_fTimeLimit = 0;
    //GameObject m_goPlayerInvCanObj;
    Canvas m_canPlayerInvCan;
    List<TMP_Text> m_ltTextList;
    List<UnityEngine.UI.Image> m_lgoSlots;
    Player m_pPlayer;

    GameObject rtCanvasHolder;
    List<UnityEngine.UI.Image> Outline = new List<UnityEngine.UI.Image>();
    GameObject TextHolder;
    UnityEngine.UI.Image LastOutline;
    [SerializeField] float m_fInvFullTextOpa = .1f;
    Color m_cInvFullColor;
    [SerializeField] float m_fInvFullTextTimer = 0;
    [SerializeField] float m_fInvFullTextTimeLimit = 0;
    Color m_cOrigOutlineColor = new Color(0.9245283f, 0.9245283f, 0.9245283f, 0.3843137f);
    char[] nNumDelim = { '1', '2', '3', '4', '5', '6', '7', '8', '9', '0' };

    // Start is called before the first frame update
    void Start()
    {
        rtCanvasHolder = transform.GetChild(0).gameObject;
        TextHolder = rtCanvasHolder.transform.GetChild(rtCanvasHolder.transform.childCount - 1).gameObject;
        m_cInvFullColor = TextHolder.transform.GetChild(0).GetComponent<TMP_Text>().color;
        TextHolder.transform.GetChild(0).GetComponent<TMP_Text>().color = Color.clear;

        for (int i = 0; i < rtCanvasHolder.transform.childCount - 1; i++)
        {
            Outline.Add(rtCanvasHolder.transform.GetChild(i).GetComponent<UnityEngine.UI.Image>());
        }
        LastOutline = Outline[0];

        m_pPlayer = GameObject.FindGameObjectWithTag("Player").GetComponent<Player>();
        m_ltTextList = new List<TMP_Text>();

        for (int i = 0; i < Outline.Count; i++)
        {
            for (int j = 0; j < Outline[i].transform.childCount; j++)
            {
                var Child = Outline[i].transform.GetChild(j);

                if (Child.GetComponent<TMP_Text>() != null)
                {
                    TMP_Text ItemText = Outline[i].transform.GetChild(j).GetComponent<TMP_Text>();
                    m_ltTextList.Add(ItemText);
                }
            }
        }

        //m_canPlayerInvCan = GetComponent<Canvas>();
        //m_lgoSlots = new List<UnityEngine.UI.Image>();
        //for (int i = 0; i < m_canPlayerInvCan.transform.childCount; i++)
        //{
        //    m_lgoSlots.Add(m_canPlayerInvCan.transform.GetChild(i).GetComponent<UnityEngine.UI.Image>());
        //}
    }

    // Update is called once per frame
    void Update()
    {
        //Removes items from UI
        if (m_ltTextList.Count > m_pPlayer.GetInventory().Count)
        {
            for (int i = m_pPlayer.GetInventory().Count; i < m_ltTextList.Count; i++)
            {
                m_ltTextList[i].text = "";
            }
        }

        for (int i = 0; i < m_pPlayer.GetInventory().Count; i++)
        {
            string[] sItemName = { m_pPlayer.GetInventory()[i].name };
            string sOrigName = m_pPlayer.GetInventory()[i].name;
            for (int j = 0; j < sItemName[0].Length; j++)
            {

                if (sItemName[0][j] == '(')
                {
                    sItemName = sItemName[0].Split(sItemName[0][j]);
                }

                if (sOrigName[j] == '_')
                {
                    sItemName[0] = sOrigName.Replace(sOrigName[j], ' ');
                    sOrigName = sItemName[0];
                }

                for (int k = 0; k < nNumDelim.Length; k++)
                {
                    if (sOrigName[j] == nNumDelim[k])
                    {
                        sItemName = sOrigName.Split(sOrigName[j]);
                    }
                }

                m_ltTextList[i].text = sItemName[0];
            }
        }

        if (m_pPlayer.GetInventory().Count != 0)
        {
            if (!m_pPlayer.g_bScrolling)
            {
                Outline[0].color = TextHolder.transform.GetChild(1).GetComponent<TMP_Text>().color;
                
                for (int i = 0; i < Outline.Count; i++)
                {
                    for (int j = 0; j < Outline[i].transform.childCount; j++)
                    {
                        if (i != 0)
                        {
                            
                            if (Outline[i].color == TextHolder.transform.GetChild(1).GetComponent<TMP_Text>().color)
                            {
                                Outline[i].color = m_cOrigOutlineColor;
                            }
                        }
                    }
                }
            }
            else
            {
                
                for (int i = 0; i < Outline.Count; i++)
                {
                    for (int j = 0; j < Outline[i].transform.childCount; j++)
                    {
                        if (Outline[i].transform.GetChild(j).gameObject.GetComponent<TMP_Text>() != null)
                        {
                            if (Outline[i].transform.GetChild(j).gameObject.GetComponent<TMP_Text>().text != "")
                            {
                                if (i != 0)
                                {
                                    Outline[i].color = TextHolder.transform.GetChild(1).GetComponent<TMP_Text>().color;
                                    if (Outline[i - 1].color == TextHolder.transform.GetChild(1).GetComponent<TMP_Text>().color)
                                    {
                                        Outline[i - 1].color = m_cOrigOutlineColor;
                                    }
                                    break;
                                }
                                if (i == Outline.Count)
                                {
                                    Outline[4].color = TextHolder.transform.GetChild(1).GetComponent<TMP_Text>().color;
                                }
                            }
                        }
                    }
                }
            }


        }
        else
        {
            for (int i = 0; i < Outline.Count; i++)
            {
                Outline[i].color = m_cOrigOutlineColor;
            }
        }
        DisplayFull();
    }

    public void DisplayFull()
    {
        if (m_pPlayer.IsInvFull())
        {
            m_fInvFullTextTimer = 0;
            if (TextHolder.transform.GetChild(0).GetComponent<TMP_Text>().color.a < m_cInvFullColor.a)
            {
                for (float i = 0; i < m_cInvFullColor.a; i++)
                {
                    m_cInvFullColor += new Color(0, 0, 0, m_fInvFullTextOpa);
                    TextHolder.transform.GetChild(0).GetComponent<TMP_Text>().color += (m_cInvFullColor * Time.deltaTime) / 100;
                }
            }
        }
        else
        {
            m_fInvFullTextTimer += Time.deltaTime;
            if (TextHolder.transform.GetChild(0).GetComponent<TMP_Text>().color.a > 0 && m_fInvFullTextTimer >= m_fInvFullTextTimeLimit)
            {
                m_cInvFullColor -= new Color(0, 0, 0, m_fInvFullTextOpa) * Time.deltaTime;
                TextHolder.transform.GetChild(0).GetComponent<TMP_Text>().color -= m_cInvFullColor;

                m_fInvFullTextTimer = 0;
            }
        }
    }
}

