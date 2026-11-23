// Lit la constante SIMULATION (fichier export/etats.js) et joue l'animation.
// SIMULATION = { lignes, colonnes, regle, etats: ["....o..X...", ...] }
// etats[g] = une chaine par generation : lignes x colonnes symboles ('.', 'o', 'X')

const COULEUR_PROIE = "#33cc33";
const COULEUR_PREDATEUR = "#ff3333";

const info = document.getElementById("info");
const canvas = document.getElementById("grille");
const ctx = canvas.getContext("2d");
const courbe = document.getElementById("courbe");
const ctxCourbe = courbe.getContext("2d");
const bouton = document.getElementById("bouton-lecture");
const curseurGen = document.getElementById("curseur-generation");
const curseurVitesse = document.getElementById("curseur-vitesse");
const texteGen = document.getElementById("numero-generation");
const texteVitesse = document.getElementById("valeur-vitesse");
const compteurs = document.getElementById("compteurs");

// etats.js absent : on explique quoi faire au lieu d'une page vide
if (typeof SIMULATION === "undefined") {
  info.textContent = "Fichier export/etats.js introuvable : lance ./simulation, "
    + "choisis 12 (export page web) puis 1 (lancer), et recharge cette page.";
  info.className = "erreur";
  throw new Error("SIMULATION non defini");
}

const lignes = SIMULATION.lignes;
const colonnes = SIMULATION.colonnes;
const etats = SIMULATION.etats;
const nbGen = etats.length;

info.textContent = "Regle : " + SIMULATION.regle + " - " + lignes + " x " + colonnes
  + " - " + nbGen + " generations";

// taille d'une case : la plus grande qui tient dans 800 x 600
const taille = Math.max(1, Math.floor(Math.min(800 / colonnes, 600 / lignes)));
canvas.width = colonnes * taille;
canvas.height = lignes * taille;

// populations de chaque generation (calculees une fois, pour les compteurs et la courbe)
const proies = [];
const predateurs = [];
for (const etat of etats) {
  let p = 0, x = 0;
  for (const c of etat) {
    if (c === "o") p++;
    else if (c === "X") x++;
  }
  proies.push(p);
  predateurs.push(x);
}
const maxPop = Math.max(1, ...proies, ...predateurs);

let generation = 0;
let enLecture = true;
let derniereImage = 0;

curseurGen.max = nbGen - 1;

function dessinerGrille(g) {
  ctx.fillStyle = "#000000";
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  const etat = etats[g];
  for (let i = 0; i < lignes; i++) {
    for (let j = 0; j < colonnes; j++) {
      const c = etat[i * colonnes + j];
      if (c === ".") continue;
      ctx.fillStyle = (c === "o") ? COULEUR_PROIE : COULEUR_PREDATEUR;
      ctx.fillRect(j * taille, i * taille, taille - 1, taille - 1);
    }
  }
}

function dessinerCourbe(g) {
  const w = courbe.width, h = courbe.height;
  ctxCourbe.fillStyle = "#000000";
  ctxCourbe.fillRect(0, 0, w, h);
  const tracer = (valeurs, couleur) => {
    ctxCourbe.strokeStyle = couleur;
    ctxCourbe.beginPath();
    for (let k = 0; k < nbGen; k++) {
      const x = nbGen > 1 ? k * (w - 1) / (nbGen - 1) : 0;
      const y = h - 1 - valeurs[k] * (h - 6) / maxPop;
      if (k === 0) ctxCourbe.moveTo(x, y); else ctxCourbe.lineTo(x, y);
    }
    ctxCourbe.stroke();
  };
  tracer(proies, COULEUR_PROIE);
  tracer(predateurs, COULEUR_PREDATEUR);
  // trait blanc = generation affichee
  const xg = nbGen > 1 ? g * (w - 1) / (nbGen - 1) : 0;
  ctxCourbe.strokeStyle = "#ffffff";
  ctxCourbe.beginPath();
  ctxCourbe.moveTo(xg, 0);
  ctxCourbe.lineTo(xg, h);
  ctxCourbe.stroke();
}

function afficher(g) {
  generation = g;
  dessinerGrille(g);
  dessinerCourbe(g);
  curseurGen.value = g;
  texteGen.textContent = g + " / " + (nbGen - 1);
  compteurs.textContent = "Proies : " + proies[g] + "   Predateurs : " + predateurs[g];
}

function boucle(maintenant) {
  const delai = 1000 / Number(curseurVitesse.value);
  if (enLecture && maintenant - derniereImage >= delai) {
    derniereImage = maintenant;
    if (generation < nbGen - 1) {
      afficher(generation + 1);
    } else {
      enLecture = false;                  // fin : on s'arrete sur la derniere generation
      bouton.textContent = "Rejouer";
    }
  }
  requestAnimationFrame(boucle);
}

bouton.addEventListener("click", () => {
  if (generation >= nbGen - 1) afficher(0);   // "Rejouer" repart du debut
  enLecture = !enLecture;
  bouton.textContent = enLecture ? "Pause" : "Lecture";
});

curseurGen.addEventListener("input", () => {
  enLecture = false;                      // on prend la main : la lecture se met en pause
  bouton.textContent = "Lecture";
  afficher(Number(curseurGen.value));
});

curseurVitesse.addEventListener("input", () => {
  texteVitesse.textContent = curseurVitesse.value + " gen/s";
});

afficher(0);
requestAnimationFrame(boucle);
