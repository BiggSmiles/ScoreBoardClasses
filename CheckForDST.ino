
// DOW is 0 - 6

bool IsDST(int day, int month, int dow)

{
	//  DST starts  2nd sunday in March and ends the first sunday in November


	if (month < 3 || month > 11) {

		return false;  	 // it's  one of these months: january, Febuary or december

	}

	//April to October are in

	if (month > 3 && month < 11) {

		return true; // still in DST - Match, April, May, June, July, August, September, October are the DST months

	}

	int previousSunday = day - dow;

	//In march, we are DST if our previous sunday was on or after the 8th.

	if (month == 3) {

		return previousSunday >= 8;

	}

	//In november we must be before the first sunday to be dst.

	//That means the previous sunday must be before the 1st.
	//	Serial.print("PreviousSunday: "); Serial.println(previousSunday <=0);

	return previousSunday <= 0;

}