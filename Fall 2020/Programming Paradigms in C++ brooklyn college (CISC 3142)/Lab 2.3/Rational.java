public class Rational{
	
	public static void main (String args) {
		Person m = new Person (new Name("mohamed", "Shafee"), 27);
		System.out.println(Person.x);
	}
	private int numerator, denominator;
	
	Rational(){
		this(0);
	}
	
	Rational(int numerator){
		this(numerator, 1);
	}
	
	Rational(Rational rational){
		this(rational.getNumerator(),rational.getDenominator());
	}
	
	Rational(int numerator, int denominator){
		if (denominator == 0) {
            throw new RationalException("Denominator can't be zero!");
        }
		this.numerator = numerator/gcd(numerator,denominator);
		this.denominator = denominator/gcd(numerator,denominator);
	}
	
	public Rational negate() {
		return new Rational(-1*this.numerator, this.denominator);
	}
	
	public Rational inverse() {
		return new Rational(this.denominator, this.numerator);
	}
	
	public Rational add( Rational operande) {
		return new Rational(
				this.numerator* operande.denominator + operande.getNumerator()*this.getDenominator(),
				this.denominator*operande.denominator
				);
	}
	
	public Rational sub(Rational operande){
		return this.add(operande.negate());
	}
	
	public Rational mul( Rational operande){
		return new Rational(this.numerator*operande.getNumerator(), this.denominator*operande.getDenominator());
	}
	
	public Rational div( Rational operande){
		return this.mul(operande.inverse());
	}
	
	public int getNumerator() {
		return this.numerator;
	}
	
	public int getDenominator() {
		return this.denominator;
	}
	
	private int gcd(int numerator, int denominator) {
		if (denominator == 0)
			return numerator;
		else
			return gcd(denominator, numerator%denominator);
	}
	
	public void addInPlace(Rational operande) {
		Rational temp = this.add(operande);
		this.numerator = temp.getNumerator();
		this.denominator = temp.getDenominator();
	}
	
	public void subInPlace(Rational operande) {
		Rational temp = this.sub(operande);
		this.numerator = temp.getNumerator();
		this.denominator = temp.getDenominator();
	}
	
	public void divInPlace( Rational operande) {
		Rational temp = this.div(operande);
		this.numerator = temp.getNumerator();
		this.denominator = temp.getDenominator();
	}
	
	public void mulInPlace( Rational operande) {
		Rational temp = this.mul(operande);
		this.numerator = temp.getNumerator();
		this.denominator = temp.getDenominator();
	}
	
	public int compareTo(Rational operande) {
		float a = (float)this.getNumerator()/(float)this.getDenominator();
		float b = (float)operande.getNumerator()/(float)operande.getDenominator();
		if (a < b)
			return -1;
		else if (Math.abs(a-b) <= 0.0001) 
			return 0;
		else
			return 1;
	}
	
	public boolean equals(Rational operande) {
		return (this.compareTo(operande) == 0);
	}
	
	public String toString() {
		return this.denominator == 1 ? Integer.toString(this.numerator) :
		this.numerator == this.denominator? "1":
		Integer.toString(this.numerator) + "/" + Integer.toString(this.denominator);
	}
}