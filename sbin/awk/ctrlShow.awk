#!/usr/bin/awk -f
BEGIN {
	FS = "\"[ ]*,[ ]*\"";
	OptionIndex = 0;
	printf("(%2s) %-5s(%-10s) : %-10s (%2s)%15s = %-10s : %-10s : %s\n", "NN", "Opt", "FullOption", "Importance",
																   "nn","VariableName", "InitValue", "Type",
																   "Additional Message");
	printf("----------------------------------------------------------------------------------------------------------\n");

}

/^[^#]/ {
	OptionField       = 1;
	FullOptionField   = 2;
	AdditionalMessage = 3;
	Importance        = 4;
	StartField        = 5; # Set field where required argument number 
	FieldNumber       = 4; # Set required field number per one argument 
	FieldIndex        = 1;
	FieldVariable     = 2;
	FieldType         = 3;
	FieldInitialValue = 4;

	OptionIndex++;
	argNumber = $StartField; # Get number of argumentNumber 
	printf("(%2d) %-5s(%-10s) : %-10s ", OptionIndex, $OptionField, $FullOptionField, $Importance);
	for(i=0; i<argNumber; i++) {
		getEachField(i);
		printf("(%2d)%15s = %-10s : %-10s ", Index, Variable, Init, Type);
	}
	printf(": %s\n", $AdditionalMessage)
}

END {
}
