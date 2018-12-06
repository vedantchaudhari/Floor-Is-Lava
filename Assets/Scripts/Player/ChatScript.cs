using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
public class ChatScript : MonoBehaviour
{
    public Text chatBox;
    public InputField chatInput;

    bool usingChat = false;

    // Start is called before the first frame update
    void Start()
    {
        chatInput.DeactivateInputField();
    }

    // Update is called once per frame
    void Update()
    {
        inputCheck();
        print(chatInput.IsActive());
        print(usingChat);
    }

    void inputCheck()
    {
        if (Input.GetKeyDown(KeyCode.KeypadEnter))
        {
            if (chatInput.GetComponent<Text>())
                sendChat();
            toggleChatActivity();
        }
        if(usingChat)
        {
        }
    }

    void toggleChatActivity()
    {
       
        usingChat = !usingChat;
        if (usingChat)
            chatInput.ActivateInputField();
        else
            chatInput.DeactivateInputField();
    }

    void sendChat()
    {

    }
}
