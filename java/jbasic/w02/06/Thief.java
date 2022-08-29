public class Thief implements MailService {
    private int minPrice = 0;
    private int storePrice = 0;

    public Thief(int price)
    {
        this.minPrice = price;
    }

    public int getStolenValue()
    {
        return storePrice;
    }

    @Override
    public Sendable processMail(Sendable mail)
    {
        if(mail.getClass() == MailPackage.class)
        {
            Package pk = ((MailPackage)mail).getContent();
            if(pk.getPrice() >= minPrice){
                storePrice += pk.getPrice();
                mail = new MailPackage(mail.getFrom(), mail.getTo(), new Package("stones instead of " + pk.getContent(), 0));
            }
        }
        return mail;
    }
}
