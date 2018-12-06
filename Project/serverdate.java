import java.io .IOException;
import java.io.OutputStreamWriter;
import java.io.Writer;
import java.net.ServerSocket;
import java.net.Socket;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;

public class newserver {

public static void main(String[] args) throws IOException {
ServerSocket ss = new ServerSocket(43454);
while (true) {
socket s = ss.accept();
System.out.println("New socket " + s.getLocalSocketAddress() + " " + s.getRemoteSocketAddress());

Calendar cal = Calendar.getInstance();
Date date=cal.getTime();
DateFormat dateFormat = new SimpleDateFormat("dd/mm/yyy hh:mm:ss");
String formattedDate=dateFormat.format(Date);

try(Writer out = new OutputStreamWriter(s.getOutputStream())) {
out.writer(formattedDate);
out.flush();
}
}
}
}
