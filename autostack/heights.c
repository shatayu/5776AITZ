int heightsToCones(int cone) {
	int heights[15];
	heights[0] = 1650;
	heights[1] = 1700; // tuned
	heights[2] = 1740; // tuned
	heights[3] = 1790; // tuned
	heights[4] = 1850; // tuned
	heights[5] = 1900; // tuned
	heights[6] = 1960; // tuned
	heights[7] = 2020; // tuned
	heights[8] = 2070; // tuned
	heights[9] = 2180; // tuned
	heights[10] = 2260; // tuned
	heights[11] = 2420; // tuned
	heights[12] = 2600; // tuned
	heights[13] = 3140;
	heights[14] = 3140;

	int result = -1;
	if (cone >= 0 && cone <= 14) {
		result = heights[cone];
	}
	return result;
}
