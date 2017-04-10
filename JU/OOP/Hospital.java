import java.io.*;
import java.util.*;

class Observation
{
	private String observationName, observationValue;

	public Observation(String name, String value) {
		this.observationName = name;
		this.observationValue = value;
	}

	public void setName(String name) {
		this.observationName = name;
	}

	public void setValue(String value) {
		this.observationValue = value;
	}

	public String getName() {
		return this.observationName;
	}

	public String getValue() {
		return this.observationValue;
	}
}

class Patient
{
	String name;
	String doctor;
	ArrayList<Observation> observations;
	int socialSecurityNumber;
	boolean admitted;
	Date admitDate;
	
	public Patient(int socialSecurityNumber, String name) {
		this(socialSecurityNumber, name, null);
	}

	public Patient(int socialSecurityNumber, String name, String doctor) {
		this.socialSecurityNumber = socialSecurityNumber;
		this.name = name;
		this.doctor = doctor;
		this.observations = new ArrayList<Observation>();
		this.admitted = false;
	}

	public void assignDoctor(String doctor) {
		this.doctor = doctor;
	}

	public void addObservation(String obsName, String obsValue) {
		Observation obs = new Observation(obsName, obsValue);
		observations.add(obs);
	}

	public void printObservations() {
		System.out.println("Observations: ");
		for(Observation o : observations) {
			System.out.println(o.getName() + ": " + o.getValue());
		}
	}

	public void printDetails() {
		System.out.println("Name: " + this.name);
		System.out.println("Doctor's name: " + this.doctor);
		System.out.println("Admit date: " + this.admitDate);
		printObservations();
	}

	public int getSocialSecurityNumber() {
		return socialSecurityNumber;
	}

	public String getDoctor() {
		return doctor;
	}

	public void setAdmitted() {
		this.admitted = true;
		this.admitDate = new Date();
	}

	public boolean isAdmitted() {
		return this.admitted;
	}
}

class HospitalManagement
{
	ArrayList<Patient> patients;

	public HospitalManagement() {
		patients = new ArrayList<Patient>();
	}

	public void addPatient(Patient p) {
		patients.add(p);
	}

	public boolean admitPatient(Patient p) {
		if(!p.isAdmitted())
			return false;
		patients.add(p);
		return true;
	}

	public boolean admitPatient(Patient p, String doctor) {
		p.assignDoctor(doctor);
		p.setAdmitted();
		return admitPatient(p);
	}

	public Patient searchPatient(int socialSecurityNumber) {
		for(Patient p : patients) {
			if(p.getSocialSecurityNumber() == socialSecurityNumber)
				return p;
		}
		return null;
	}
}

public class Hospital
{
	public static void main(String[] args) throws IOException {
		Scanner sc = new Scanner(System.in);
		System.out.println("1. Register Patient");
		System.out.println("2. Admit Patient");
		System.out.println("3. Record Observations");
		System.out.println("4. Print patient details");
		System.out.println("5. Exit");
		HospitalManagement hm = new HospitalManagement();
		while(true) {
			System.out.print("Enter choice: ");
			int choice = sc.nextInt();
			sc.nextLine();
			switch(choice) {
				case 1:
					{
						System.out.print("Enter Patient Name: ");
						String name = sc.nextLine();
						System.out.print("Enter Social-Security-Number: ");
						int scn = sc.nextInt();
						sc.nextLine();
						Patient p = new Patient(scn, name);
						hm.addPatient(p);
					}
					break;
				case 2:
					{
						System.out.print("Enter Social-Security-Number: ");
						int scn = sc.nextInt();
						sc.nextLine();
						Patient p = hm.searchPatient(scn);
						if(p == null) {
							System.out.println("Patient not found!");
							break;
						}
						if(!hm.admitPatient(p)) {
							String doctor = p.getDoctor();
							if(doctor == null) {
								System.out.print("Enter name of doctor assigned: ");
								doctor = sc.nextLine();
							}
							if(!hm.admitPatient(p, doctor)) {
								System.out.println("Unsuccessful!");
								break;
							}
						}
						System.out.println("Successful!");
					}
					break;
				case 3:
					{
						System.out.print("Enter Social-Security-Number: ");
						int scn = sc.nextInt();
						sc.nextLine();
						Patient p = hm.searchPatient(scn);
						if(p == null) {
							System.out.println("Patient not found!");
							break;
						}
						if(!p.isAdmitted()) {
							System.out.println("Admit Patient first!");
							break;
						}
						while(true) {
							System.out.print("Enter observation name: ");
							String name = sc.nextLine();
							System.out.print("Enter observation value: ");
							String value = sc.nextLine();
							p.addObservation(name, value);
							System.out.print("Do you want to add more observations(y/n): ");
							char cont = sc.nextLine().charAt(0);
							if(cont != 'y' && cont != 'Y')
								break;
						}
					}
					break;
				case 4:
					{
						System.out.print("Enter Social-Security-Number: ");
						int scn = sc.nextInt();
						sc.nextLine();
						Patient p = hm.searchPatient(scn);
						if(p == null) {
							System.out.println("Patient not found!");
							break;
						}
						p.printDetails();
					}
					break;
				case 5:
					break;
				default:
					System.out.println("Invalid Choice!");
			}
			if(choice == 5)
				break;
		}
	}
}