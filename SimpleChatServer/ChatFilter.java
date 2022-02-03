import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class ChatFilter{
    private final List<String> bannedWords = new ArrayList<>();

    public ChatFilter(String badWordsFileName) throws IOException {
        String filePath = System.getProperty("user.dir");
        filePath = filePath +"/"+ badWordsFileName;

        FileReader fileToRead = new FileReader(filePath);
        BufferedReader bf = new BufferedReader(fileToRead);

        System.out.println("Banned Words!");
        String badWord;
        while((badWord = bf.readLine()) != null){
            bannedWords.add(badWord);
            System.out.println(badWord);
        }

        bf.close();
    }

    public String filter(String msg) {
        String[] wordsInMsg = msg.split(" ");

        for(int j = 0; j<wordsInMsg.length ; j++)
        {
            if(bannedWords.contains(wordsInMsg[j]))
            {
                int sizeOfStr = wordsInMsg[j].length();
                wordsInMsg[j] = "";
                for (int i = 0; i < sizeOfStr; i++) {
                    wordsInMsg[j] = wordsInMsg[j] + "*";
                }
            }
        }

        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < wordsInMsg.length; i++) {
            sb.append(wordsInMsg[i] + " ");
        }

        return sb.toString();
    }
}
