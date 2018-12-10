import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.math.BigInteger;
import java.security.PublicKey;
import java.security.cert.CertificateException;
import java.security.cert.CertificateFactory;
import java.security.cert.X509Certificate;
import java.security.interfaces.RSAPublicKey;
import java.text.SimpleDateFormat;
import java.util.Collection;
import java.util.Date;
import java.util.List;

public class Certificate {
	public static void main(String[] args) throws CertificateException, FileNotFoundException {
		CertificateFactory cf = CertificateFactory.getInstance("X.509");
		X509Certificate cert_info = (X509Certificate)cf.generateCertificate(new FileInputStream("D:\\大三上\\2016级\\Web安全\\HW3\\c.cer"));
		String public_key_string = "00" + ((RSAPublicKey) cert_info.getPublicKey()).getModulus().toString(16);
		int public_key_length = public_key_string.length()*4 - 8;
		// String signature = (cert_info.getEncoded()).getModulus().toString(16);
		String str_signature = (new BigInteger(cert_info.getSignature())).toString(16);
		// String  = t.toString(16);
		// System.out.println(str_signature.length());
		
		System.out.println("Certificate:");
		System.out.println("    Data:");
		System.out.println("        Version: " + cert_info.getVersion());
		System.out.println("        Serial Number:");
		// System.out.println(cert_info.getSerialNumber().toString(16));
		System.out.println("            " + stringFormat(cert_info.getSerialNumber().toString(16)));
		System.out.println("    Signature Algorithm: " + cert_info.getPublicKey().getAlgorithm());
		System.out.println("        Issuer: " + cert_info.getIssuerDN());
		System.out.println("        Validity");
		System.out.println("            Not Before: " + cert_info.getNotBefore());
		System.out.println("            Not After : " + cert_info.getNotAfter());
		System.out.println("        Subject: " + cert_info.getSubjectDN());
		System.out.println("        Subject Public Key Info:");
		System.out.println("            Public Key Algorithm: " + cert_info.getPublicKey().getAlgorithm());
		System.out.println("                Public-Key: (" + public_key_length + " bit)");
		System.out.println("                Modulus: ");
		stringFormat2(public_key_string);
		System.out.println("                Exponent: " + ((RSAPublicKey) cert_info.getPublicKey()).getPublicExponent() + " (0x" + ((RSAPublicKey) cert_info.getPublicKey()).getPublicExponent().toString(16) + ")");
		// System.out.println(cert_info.get);
		System.out.println("    Signature Algorithm: " + cert_info.getSigAlgName());
		// System.out.println(cert_info.getSignature());
		stringFormat3(str_signature);
	}

	static String stringFormat(String str) {
		
		if (str.length() % 2 != 0)
			str = "0" + str;
		
		String temp = "";
		for (int i = 0; i < str.length(); i++) {
			if ((i+1) % 2 == 0 && i != str.length()-1) {
				temp += str.charAt(i);
				temp += ":";				
			}
			else {
				temp += str.charAt(i);
			}
		}
		return temp;
	}
	
	static String stringFormat2(String str) {
		for (int i = 0; i < str.length(); i++) {
			if (i % 30 == 0) {
				System.out.print("                    " + str.charAt(i));
			}
			else if ((i+1) % 2 == 0 && i % 30 != 29 && i != str.length()-1) {
				System.out.print(str.charAt(i));
				System.out.print(":");
			}
			else if (i % 30 == 29) {
				System.out.println(str.charAt(i));
			}
			else {
				System.out.print(str.charAt(i));
			}
		}
		System.out.print("\n");		
		return str;
	}
	
	static String stringFormat3(String str) {
		for (int i = 0; i < str.length(); i++) {
			if (i % 36 == 0) {
				System.out.print("         " + str.charAt(i));
			}
			else if ((i+1) % 2 == 0 && i % 36 != 35 && i != str.length()-1) {
				System.out.print(str.charAt(i));
				System.out.print(":");
			}
			else if (i % 36 == 35) {
				System.out.println(str.charAt(i));
			}
			else {
				System.out.print(str.charAt(i));
			}
		}
		System.out.print("\n");		
		return str;
	}
}


