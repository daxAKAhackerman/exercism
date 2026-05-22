#include "allergies.h"

bool is_allergic_to(allergen_t allergen, uint32_t score) {
  return (score >> allergen) & 0x01;
}

allergen_list_t get_allergens(uint32_t score) {
  allergen_list_t allergens = {.count = __builtin_popcount(score & 0xFF),
                               {
                                   (score >> ALLERGEN_EGGS) & 0x01,
                                   (score >> ALLERGEN_PEANUTS) & 0x01,
                                   (score >> ALLERGEN_SHELLFISH) & 0x01,
                                   (score >> ALLERGEN_STRAWBERRIES) & 0x01,
                                   (score >> ALLERGEN_TOMATOES) & 0x01,
                                   (score >> ALLERGEN_CHOCOLATE) & 0x01,
                                   (score >> ALLERGEN_POLLEN) & 0x01,
                                   (score >> ALLERGEN_CATS) & 0x01,
                               }};

  return allergens;
}
