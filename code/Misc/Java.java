// java.util.*, java.math.*, java.io.*
public class Main{ // BufferedReader, BufferedWriter
public static void main(String[] args) throws IOException {
br=new BufferedReader(new InputStreamReader(System.in));
bw=new BufferedWriter(new OutputStreamWriter(System.out));
String[] ar = br.readLine().split(" ");
int a=Integer.parseInt(ar[0]), b=Integer.parseInt(ar[1]);
bw.write(String.valueOf(a+b)+"\n");br.close();bw.close();
ArrayList<Integer> a = new ArrayList<>();
a.add(1234); a.get(0); a.remove(a.size()-1); a.clear();
}}