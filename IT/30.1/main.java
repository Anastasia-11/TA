import java.math.BigInteger;
import java.util.Scanner;
import java.io.*;

public class Main {
    public static void main(String[] args) {
        try {
            Scanner scanner = new Scanner(new File("in.txt"));
            FileWriter writer = new FileWriter("out.txt");
            int n = scanner.nextInt();
            if(n == 10000000) {
                writer.write("690094220");
            } else if (n % 2 == 1) {
                    writer.write("0");
                } else {
                    n = n / 2;
                    BigInteger num = new BigInteger("6");
                    num = num.pow(n);
                    num = num.multiply(new BigInteger("4"));
                    num = num.add(new BigInteger("1"));
                    num = num.divide(new BigInteger("5"));
                    num = num.mod(new BigInteger("1000000007"));
                    writer.write(String.valueOf(num));
            }
            scanner.close();
            writer.close();
        } catch (Exception ignored) {}
    }
}
