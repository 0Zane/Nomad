#include "string"



const std::string questions[10] = {
  "What is the rule of 3 in survival?",
  "How much water do you need per day?",
  "How to purify water in the wild?",
  "How to find the best spot for an emergency shelter?",
  "How to navigate without GPS or compass?",
  "How to signal for help?",
  "What are the early signs of hypothermia?",
  "How to manage panic in a survival situation?",
  "What foods should you avoid in the wild?",
  "How to treat a sprained ankle with no medical kit?"
};

const std::string answers[10] = {
  "3 minutes without oxygen, 3 hours in extreme cold without shelter, 3 days without water, 3 weeks without food. This hierarchy guides all your priorities.",
  "At least 2L per day at rest. In heat or during effort, up to 4-6L. Never wait until you are thirsty. Water is your top priority.",
  "Boil for 1 minute. Or use purification tablets. Or a filter like LifeStraw. Clear water is not necessarily safe to drink.",
  "Mid-slope, sheltered from wind, facing morning sun. Never in a hollow or dry riverbed. Insulate yourself from the ground - you lose more heat through the ground than through wind.",
  "Sun rises in the east, sets in the west. At night, find the Big Dipper and follow its edge stars to Polaris - that is North.",
  "3 signals in a triangle is the universal distress code - fires, rocks, or any visible marks. A mirror or shiny surface can be seen up to 15 km away. Stay in place once you have signaled.",
  "Intense shivering, confusion, slurred speech, loss of coordination. Get out of the wind, remove wet clothing, insulate from the ground, and warm the core first.",
  "Use the STOP rule: Stop, Think, Observe, Plan. Most fatal mistakes happen in the first minutes of panic. One action at a time.",
  "White or yellow berries, plants with white sap, mushrooms you cannot identify with certainty. When in doubt, do not eat it. You can survive 3 weeks without food.",
  "Rest, cool it in a stream, wrap it firmly, keep it elevated. A mild sprain can still walk with good support. If the ankle is unstable or very swollen, do not put weight on it."
};

std::string gettip(int question_ID);