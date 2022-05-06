public abstract class KeywordAnalyzer implements TextAnalyzer {

    public KeywordAnalyzer()
    {}

    protected abstract String[] getKeywords();
    protected abstract Label getLabel();

    @Override
    public Label processText(String text) {
        for(int i = 0; i < getKeywords().length; ++i) {
            if(text.indexOf(getKeywords()[i]) != -1) {
                return getLabel();
            } else {
                continue;
            }
        }
        return Label.OK;
    }
}
