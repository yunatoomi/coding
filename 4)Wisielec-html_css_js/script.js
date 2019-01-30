var cars = ["VOLKSWAGEN", "CHEVROLET", "JAGUAR", "FERRARI", "MITSUBISHI", "LEXUS", "PORSCHE", "NISSAN", "CADILLAC", "LAMBORGHINI"];
var animals = ["ALBATROS", "ŚLIMAK", "TYGRYS", "CHRZĄSZCZ", "KAMELEON", "KOT", "SOKÓŁ", "ORZEŁ", "ŻYRAFA", "CHOMIK"];
var countries = ["MAROKO", "EKWADOR", "FRANCJA", "HISZPANIA", "NIEMCY", "PORTUGALIA", "SZWECJA", "WATYKAN", "UGANDA", "NORWEGIA"];
var alfabet ="QAĄBCĆDEĘFGHIJKLŁMNŃOÓPRSŚTUWYZŹŻVX";
var but1 = document.getElementById("but1");
var but2 = document.getElementById("but2");
var but3 = document.getElementById("but3");
var kat = document.getElementById("kat");
var wordd = document.getElementById("word");
var table = document.getElementById("table");
var w1 = document.getElementById("w1");
var w2 = document.getElementById("w2");
var w3 = document.getElementById("w3");
var w4 = document.getElementById("w4");
var w5 = document.getElementById("w5");
var w6 = document.getElementById("w6");
var w7 = document.getElementById("w7");
var w8 = document.getElementById("w8");
var w9 = document.getElementById("w9");
var w10 = document.getElementById("w10");
var w11 = document.getElementById("w11");
var odp = document.getElementById("answer");
var failfield = document.getElementById("fails");
var healthbar = document.getElementById("healthbar");
var game_over = document.getElementById("gameover");
var viictory = document.getElementById("victory");
var rest = document.getElementById("restart");
var grafika = document.getElementsByClassName("grafika");
var flit = alfabet;
var answer;
var word = "*";
var n = 0;

function init(kategoria){
	but1.style.display = "none";
	but2.style.display = "none";
	but3.style.display = "none";
	table.style.display = "table";
	wordd.style.display = "table";
	switch(kategoria){
		case 1:
			kat.textContent ="Kategoria:Samochódy";
			answer = cars[Math.floor(Math.random() * 10)];
			break;
		case 2:
			kat.textContent ="Kategoria:Zwierzęta";
			answer = animals[Math.floor(Math.random() * 10)];
			break;
		case 3:
			kat.textContent ="Kategoria:Geografia";
			answer = countries[Math.floor(Math.random() * 10)];
			break;
	}
	for(var i = 1;i<answer.length;++i){
				word = word + "*";
			}
			switch(answer.length){
				case 10:
					w11.style.display = "none";
					break;
				case 9:
					w11.style.display = "none";
					w10.style.display = "none";
					break;
				case 8:
					w11.style.display = "none";
					w10.style.display = "none";
					w9.style.display = "none";
					break;
				case 7:
					w11.style.display = "none";
					w10.style.display = "none";
					w9.style.display = "none";
					w8.style.display = "none";
					break;
				case 6:
					w11.style.display = "none";
					w10.style.display = "none";
					w9.style.display = "none";
					w8.style.display = "none";
					w7.style.display = "none";
					break;
				case 5:
					w11.style.display = "none";
					w10.style.display = "none";
					w9.style.display = "none";
					w8.style.display = "none";
					w7.style.display = "none";
					w6.style.display = "none";
					break;
				case 4:
					w11.style.display = "none";
					w10.style.display = "none";
					w9.style.display = "none";
					w8.style.display = "none";
					w7.style.display = "none";
					w6.style.display = "none";
					w5.style.display = "none";
					break;
				case 3:
					w11.style.display = "none";
					w10.style.display = "none";
					w9.style.display = "none";
					w8.style.display = "none";
					w7.style.display = "none";
					w6.style.display = "none";
					w5.style.display = "none";
					w4.style.display = "none";
					break;
			}
			set_word(word);
}

function set_word(word){
	w1.textContent = word[0];
	w2.textContent = word[1];
	w3.textContent = word[2];
	w4.textContent = word[3];
	w5.textContent = word[4];
	w6.textContent = word[5];
	w7.textContent = word[6];
	w8.textContent = word[7];
	w9.textContent = word[8];
	w10.textContent = word[9];
	w11.textContent = word[10];
}

function gameover(){
	kat.style.display = "none";
	table.style.display = "none";
	wordd.style.marginTop = "50px";
	game_over.style.display = "block";
	rest.style.display = "block";
	rest.style.marginLeft = "320px";
	odp.textContent = answer;
}

function victory(){
	kat.style.display = "none";
	table.style.display = "none";
	wordd.style.marginTop = "50px";
	viictory.style.display = "block";
	rest.style.display = "block";
	rest.style.marginLeft = "320px";
	odp.textContent = answer;
}

function restart(){
	location.reload();
}

function ans(anum){
	if(flit.indexOf(alfabet[anum])!=(-1)){
		var fail = true;
		for(var i = 0;i<answer.length;++i){
			if(answer[i]==alfabet[anum]){
				word=word.slice(0,i)+alfabet[anum]+word.slice(i+1,answer.length);
				fail=false;
			}
		}
		if(fail==true){
			var status = healthbar.innerHTML;
			status=status.slice(0,status.length-2);
			healthbar.textContent = status;
			failfield.textContent = failfield.textContent+" "+alfabet[anum];
			flit=flit.replace(alfabet[anum],"0");
			grafika[n].style.display = "none";
			grafika[n+1].style.display = "block";
			++n;
			if(n>=5){
				gameover();
			}
		}
		if(word.includes("*")==false){
			victory();
		}
		set_word(word);
	}
}