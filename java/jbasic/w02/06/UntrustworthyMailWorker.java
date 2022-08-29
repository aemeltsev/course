public class UntrustworthyMailWorker implements MailService {

    private RealMailService realMailService = new RealMailService();
    private MailService[] thridMailService;

    public UntrustworthyMailWorker(MailService[] mails)
    {
        this.thridMailService = mails;
    }

    RealMailService getRealMailService()
    {
        return realMailService;
    }

    @Override
    public Sendable processMail(Sendable mail)
    {
        Sendable processed = mail;
        for (int i = 0; i < thridMailService.length; i++) {
            processed = thridMailService[i].processMail(processed);
        }
        return realMailService.processMail(mail);
    }
}
