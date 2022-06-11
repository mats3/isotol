 /*
 * Dies ist eine JavaScript-Umgebung.
 *
 * Geben Sie etwas JavaScript ein und führen Sie einen Rechtsklick aus oder wählen Sie aus dem Ausführen-Menü:
 * 1. Ausführen, um den ausgewählten Text zu evaluieren (Strg+R),
 * 2. Untersuchen, um den Objekt-Inspektor auf das Resultat anzuwenden (Strg+I), oder
 * 3. Anzeigen, um das Ergebnis in einem Kommentar hinter der Auswahl einzufügen. (Strg+L)
 */
'Einfügen erlauben'

function save(data, filename) {
    if (!data) {
        console.error('Console.save: No data')
        return;
    }

    if (!filename) filename = 'story.json'

    if (typeof data === "object") {
        data = JSON.stringify(data, undefined, 4)
    }

    var blob = new Blob([data], {
            type: 'text/json'
        }),
        e = document.createEvent('MouseEvents'),
        a = document.createElement('a')

    a.download = filename
    a.href = window.URL.createObjectURL(blob)
    a.dataset.downloadurl = ['text/json', a.download, a.href].join(':')
    e.initMouseEvent('click', true, false, window, 0, 0, 0, 0, 0, false, false, false, false, 0, null)
    a.dispatchEvent(e)
}

function hello() {
    let nennmassbereiche = [3, 6, 10, 14, 18, 24, 30, 40, 50, 65, 80,
                            100, 120, 140, 160, 180, 200, 225, 250, 280,
                            315, 355, 400, 450, 500];
    // input
    let nominalDiameter = document.getElementById('txtNominalDiameter');
        
    let toleranceClassShaft = document.querySelector("#ddlShaft");
    let toleranceClassHole = document.querySelector("#ddlHole");

	// input default values
	
            
	// output
    let es = document.querySelector("#txtShaftULDes");
    let ei = document.querySelector("#txtShaftLLDei");
    let ES = document.querySelector("#txtHoleULDES");
    let EI = document.querySelector("#txtHoleLLDEI");

    for (let i = 1; i < toleranceClassShaft.length; i++) {
		let fileContent = "";
		let fileName = toleranceClassShaft[i].textContent;
        for (let j = 0; j < nennmassbereiche.length; j++) {
            nominalDiameter.value = nennmassbereiche[j];
            toleranceClassShaft.selectedIndex = i;

            CalculateTolerance(this);
            deactiveInput(this);

	        fileContent += es.value + "," + ei.value + "\n";
        }
		save(fileContent, fileName);
    }

	for (let i = 1; i < toleranceClassHole.length; i++) {
		let fileContent = "";
		let fileName = toleranceClassHole[i].textContent;
        for (let j = 0; j < nennmassbereiche.length; j++) {
            nominalDiameter.value = nennmassbereiche[j];
            toleranceClassHole.selectedIndex = i;

            CalculateTolerance(this);
            deactiveInput(this);

	        fileContent += ES.value + "," + EI.value + "\n";
        }
		save(fileContent, fileName);
    }

}
