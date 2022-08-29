import java.util.Arrays;

public class RoleParser {
   private static String printTextPerRole(String[] roles, String[] textLines)
    {
        String text_path= "^\\A.+?:";
        StringBuilder result = new StringBuilder();

        for(int i = 0; i < roles.length; ++i)
        {
            result.append(roles[i].concat(":\n"));
            for(int j = 0; j < textLines.length; ++j)
            {
                if(textLines[j].startsWith(roles[i].concat(":")))
                {
                    result.append(j +1).append(")").append(textLines[j].replaceFirst(text_path, ""));
                    result.append("\n");
                }
            }
            result.append("\n");
        }
        return result.toString();

        /*
        StringBuilder[] text_roles = new StringBuilder[roles.length];

        for(int i = 0; i < roles.length; ++i){
            text_roles[i] = new StringBuilder(roles[i] + ":\n");
        }

        for(int j = 0; j < textLines.length; ++j){
            String[] text = textLines[j].split(":", 2);

            for(int k = 0; k < roles.length; ++k){
                if(text[0].equals(roles[k])){
                    text_roles[k].append(String.valueOf(j+1) + ")" + text[1] + "\n");
                    break;
                }
            }
        }

        return String.join("\n", text_roles);
        */
    }

    private static void test()
    {
        String[] roles = {"Городничий", "Аммос Федорович", "Артемий Филиппович", "Лука Лукич"};
        String[] textLines = {
                "Городничий: Я пригласил вас, господа, с тем, чтобы сообщить вам пренеприятное известие: к нам едет ревизор.",
                "Аммос Федорович: Как ревизор?",
                "Артемий Филиппович: Как ревизор?",
                "Городничий: Ревизор из Петербурга, инкогнито. И еще с секретным предписаньем.",
                "Аммос Федорович: Вот те на!",
                "Артемий Филиппович: Вот не было заботы, так подай!",
                "Лука Лукич: Господи боже! еще и с секретным предписаньем!"};
        System.out.print(printTextPerRole(roles, textLines));
    }

    public static void main(String[] args)
    {
        test();
    }
}
