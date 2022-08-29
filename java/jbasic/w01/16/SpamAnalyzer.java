import java.util.Arrays;
public class SpamAnalyzer extends KeywordAnalyzer{

    private String[] keywords;

    public SpamAnalyzer(String[] keywords) {
        this.keywords = new String[keywords.length];
        System.arraycopy(keywords, 0, this.keywords, 0, keywords.length);
    }

    @Override
    protected String[] getKeywords() {
        return keywords;
    }

    @Override
    protected Label getLabel() {
        return Label.SPAM;
    }
}
