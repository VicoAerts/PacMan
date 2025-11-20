PACMAN
🔷 1. Grid / Level Structuur
GridMap

De GridMap is de blauwdruk van elk level.

Wordt ingeladen uit een .txt-bestand.

Bevat een matrix met celtypes: wall, coin, fruit, Pacman-start, ghost-start, …

Geen SFML, geen gameplay-logica.

Geeft breedte/hoogte door aan World en Camera.

GridMap = pure leveldata.

🔷 2. Logica / Model
World

De centrale gameplay-logica van een level.

Bouwt alle entiteiten op uit de GridMap.

Beheert gameplay: beweging, botsingen, score, levens, win/loss.

Werkt volledig in tile/world-coördinaten (geen pixels).

Houdt modellen bij van Pacman, Ghosts, Walls, Collectables, …

Entity (abstract)

Basisklasse voor alle model-objecten.

Subtypes:

Pacman

Ghost

Collectable

Wall (optioneel als modelobject)

Subject / Observer

Subject (model): Pacman, Ghost, Collectable, …

Observer (view): PacmanView, GhostView, …

Stelt modellen in staat om wijzigingen door te geven aan de views zonder afhankelijk te zijn van SFML.

Model stuurt events → Views reageren automatisch.

🔷 3. View / Rendering
EntityView (abstract)

Visuele tegenhanger van een model-entiteit.

Observeert zijn model via het Observer-patroon.

Weet hoe het model getekend moet worden.

Combineert tile-posities met de Camera om correcte pixel-posities te bepalen.

Subtypes:

PacmanView

GhostView

CollectableView

WallView (optioneel)

Camera

Zet tile-posities (uit World/GridMap) om in pixel-posities (voor SFML).

Houdt rekening met:

venstergrootte

bovenste marge (leveltitel)

onderste marge (score/lives)

Maakt tekenen resolutie-onafhankelijk.

Camera = de brug tussen World en rendering.

🔷 4. State-systeem
State (abstract)

Basisklasse voor alle schermen (menu, level, pauze, …).

LevelState

De “dirigent” van één speel-level.

Houdt GridMap, World, Camera en alle EntityViews bij.

Verwerkt input → stuurt door naar World.

Update World → triggert observer-updates.

Rendered alle views + HUD (level bovenaan, score/lives onderaan).

Substates:

MenuState

PausedState

GameOverState

VictoryState

LevelState koppelt: input → logica → weergave.

🔷 5. Factories
EntityFactory

Maakt model-entiteiten (Pacman, Ghost, Collectable, …) op basis van GridMap.

ViewFactory

Maakt bijbehorende EntityViews voor de renderinglaag.

AbstractFactory (optioneel)

Overkoepelende interface die zowel model- als view-creatie standaardiseert.

Houdt de architectuur uitbreidbaar.

Factories vermijden hardcoded new overal in de code.

🟩 TL;DR (Snelle Samenvatting)

GridMap = levelstructuur

World = gameplay-logica

Entity = modelobject

EntityView = visuele representatie

Camera = world → pixels

LevelState = verbindende logica (input → update → render)

Factories = maken model & view objecten

Observer = modelwijzigingen → automatische view-updates