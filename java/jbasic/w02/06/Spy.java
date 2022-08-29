import java.util.logging.Logger;

public class Spy implements MailService {
    private Logger logger;
    public static final String AUSTIN_POWERS = "Austin Powers";

    public Spy(Logger logger)
    {
        this.logger = logger;
    }

    @Override
    public Sendable processMail(Sendable mail) {
        if (mail.getClass() == MailMessage.class){
            MailMessage mm = (MailMessage) mail;
            String from = mm.getFrom();
            String to = mm.getTo();
            if (from.equals(AUSTIN_POWERS) || to.equals(AUSTIN_POWERS)){
                logger.warning("Detected target mail correspondence: from " + from + " to " + to + " - " + mm.getMessage());
            } else {
                logger.info("Usual correspondence: from " + from + " to " + to);
            }
        }
        return mail;
    }
}
