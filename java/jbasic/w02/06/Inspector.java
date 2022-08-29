public class Inspector implements MailService {
    public static final String WEAPONS = "weapons";
    public static final String BANNED_SUBSTANCE = "banned substance";
    @Override
    public Sendable processMail(Sendable mail)
    {
        if (mail.getClass() == MailPackage.class)
        {
            Package pk = ((MailPackage)mail).getContent();
            String content = pk.getContent();
            if (content.indexOf("stones instead of ") == 0){
                throw new StolenPackageException();
            } else if (content.equals(WEAPONS) || content.equals(BANNED_SUBSTANCE)) {
                throw new IllegalPackageException();
            }
        }
        return mail;
    }
}
