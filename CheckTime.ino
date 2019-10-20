bool checktime(byte hrin, byte minin, byte *hrout, byte *minout)
{
	//
	//		Make sure time to be use fits within the same 24 hour period
	//

	if (minin > 59) {return false;}

	if (hrin > 23) {return false;}

	*hrout = hrin;
	*minout = minin;

	return true;
}
