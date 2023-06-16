/*
Dans cette fonction, une boucle for est utilisée pour extraire les trois derniers octets 
de l'adresse MAC de l'ESP32 et les stocker dans la variable chipId. La ligne de code qui fait 
cela est un peu complexe, mais elle utilise des opérations bit à bit pour décaler, masquer et 
combiner les valeurs.

Sinon, on va chercher le modèle de la Chip et le nombre de coeurs sur la Chip.
*/
	
uint32_t chipId = 0;

void setup() {
	Serial.begin(115200);
}

void loop() {
	for(int i=0; i<17; i=i+8) {
	  chipId |= ((ESP.getEfuseMac() >> (40 - i)) & 0xff) << i;
	}

	Serial.printf("ESP32 Chip model = %s Rev %d\n", ESP.getChipModel(), ESP.getChipRevision());
	Serial.printf("This chip has %d cores\n", ESP.getChipCores());
  Serial.print("Chip ID: "); Serial.println(chipId);
  
	delay(3000);

}
