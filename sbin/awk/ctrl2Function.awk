function initFieldIndex()
{
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
	
	argNumber = $StartField; # Get number of argumentNumber 
}

function getEachField(i) 
{
	Index  = $(StartField + i*FieldNumber + FieldIndex);
	Name   = $(StartField + i*FieldNumber + FieldVariable);
	TypeAll= $(StartField + i*FieldNumber + FieldType);
	TypeNum = split(TypeAll,TypeArray,"::");
	Type=TypeArray[1];
	Init = $(StartField + i*FieldNumber + FieldInitialValue);
}
