import java.io.Serializable;

final class ChatMessage implements Serializable {
    private static final long serialVersionUID = 6898543889087L;

    private String msg;
    private int msgType; // 0:Normal Msg 1:logout Msg 2:List Msg
    private String recipient;

    public String getRecipient() {
        return recipient;
    }

    public String getMsg() {
        return msg;
    }

    public int getMsgType() {
        return msgType;
    }

    public ChatMessage(String msg, int msgType, String recipient){
        this.msg = msg;
        this.msgType = msgType;
        this.recipient = recipient;
    }
}
