/**
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * 2º Curso en Grado en Ingeniería Informática
 * Computabilidad y Algoritmia
 * Práctica 7: Gramáticas en Forma Normal de Chomsky
 *
 * @author Dario Fajardo alu0101564630@ull.edu.es
 * @date 29 Oct 2023
 * @brief Este archivo define la clase Grammar utilizada para simular el
 *        funcionamiento de una gramática independiente del contexto.
 */

#include "../include/grammar.h"

Grammar::Grammar() {
  grammar_alphabet_ = {};
  non_terminal_symbols_ = {};
  starting_symbol_ = ' ';
  productions_ = {};
}

Grammar::Grammar(const std::string& file_name) {
  std::ifstream file{file_name, std::ios_base::in};
  std::string line;
  getline(file, line);
  for (int i{1}; i <= stoi(line); ++i) {
    std::string terminal;
    getline(file, terminal);
    grammar_alphabet_.Include(terminal[0]);
  }
  getline(file, line);
  for (int i{1}; i <= stoi(line); ++i) {
    std::string non_terminal;
    getline(file, non_terminal);
    if (i == 1) {
      starting_symbol_ = non_terminal[0];
    }
    non_terminal_symbols_.insert(non_terminal[0]);
  }
  getline(file, line);
  for (int i{1}; i <= stoi(line); ++i) {
    std::string production;
    getline(file, production);
    char non_terminal{production[0]};
    std::string sentential_form;
    for (int j{2}; j < production.length(); ++j) {
      sentential_form += production[j];
    }
    if (sentential_form == "&" && non_terminal != *non_terminal_symbols_.begin()) {
      std::cout << "Error: no se permiten producciones vacías en la gramática ";
      std::cout << "inicial.\n";
      exit(EXIT_FAILURE);
    }
    for (const auto& non_terminal : non_terminal_symbols_) {
      if (sentential_form == std::string{non_terminal}) {
        std::cout << "Error: no se permiten producciones unitarias en la ";
        std::cout << "gramática inicial.\n";
        exit(EXIT_FAILURE);
      }
    }
    Production new_production{non_terminal, sentential_form};
    productions_.insert(new_production);
  }
}

Grammar::Grammar(const Grammar& original_grammar) {
  grammar_alphabet_ = original_grammar.grammar_alphabet_;
  starting_symbol_ = original_grammar.starting_symbol_;
  non_terminal_symbols_ = original_grammar.non_terminal_symbols_;
  productions_ = original_grammar.productions_;
}

std::ofstream& operator<<(std::ofstream& output, const Grammar& grammar) {
  output << grammar.grammar_alphabet_.GetAlphabetSymbols().size() << std::endl;
  for (const auto& terminal : grammar.grammar_alphabet_.GetAlphabetSymbols()) {
    output << terminal << std::endl;
  }
  output << grammar.non_terminal_symbols_.size() << std::endl;
  for (const auto& non_terminal : grammar.non_terminal_symbols_) {
    output << non_terminal << std::endl;
  }
  output << grammar.productions_.size() << std::endl;
  for (const Production& current_production : grammar.productions_) {
    output << current_production.first << " " << current_production.second;
    output << std::endl;
  }
  return output;
}

std::ostream& operator<<(std::ostream& output, const Grammar& grammar) {
  output << grammar.grammar_alphabet_.GetAlphabetSymbols().size() << std::endl;
  for (const auto& terminal : grammar.grammar_alphabet_.GetAlphabetSymbols()) {
    output << terminal << std::endl;
  }
  output << grammar.non_terminal_symbols_.size() << std::endl;
  for (const auto& non_terminal : grammar.non_terminal_symbols_) {
    output << non_terminal << std::endl;
  }
  output << grammar.productions_.size() << std::endl;
  for (const Production& current_production : grammar.productions_) {
    output << current_production.first << " " << current_production.second;
    output << std::endl;
  }
  return output;
}

Grammar Grammar::ChomskyNormalForm() const {
  Grammar normalized_grammar{*this};
  normalized_grammar.productions_.clear();
  ProductionSet first_step_productions;
  // for all (A → X1X2 . . . Xn (con n ≥ 2, Xi ∈ (Σ ∪ V )) do
  for (const Production& current_production : productions_) {
    if (current_production.second.Length() >= 2) {
      // for all (Xi) do
      Production converted_production;
      converted_production.second = current_production.second;
      for (const auto current_symbol : current_production.second.GetSymbols()) {
        // if (Xi = a ∈ Σ) then
        if (grammar_alphabet_.GetAlphabetSymbols().count(current_symbol)) {
          std::cout << current_symbol << std::endl;
          // Add the production Ca → a;
          Production new_terminal_production;
          new_terminal_production.first = normalized_grammar.BiggestNonTerminal() + 1;
          new_terminal_production.second = String{std::string{current_symbol}};
          char non_terminal{new_terminal_production.first};
          if (!normalized_grammar.NormalizedProductionExists(new_terminal_production)) {
            normalized_grammar.non_terminal_symbols_.insert(normalized_grammar.
            BiggestNonTerminal() + 1);
            first_step_productions.insert(new_terminal_production);
            normalized_grammar.productions_.insert(new_terminal_production);
          } else {
            for (const Production& already_created_production : first_step_productions) {
              if (already_created_production.second.GetSymbols() == 
              std::string{current_symbol}) {
                non_terminal = already_created_production.first;
              }
            }
          }
          // Replace Xi with Ca in A → X1X2 . . . Xn:
          converted_production.first = current_production.first;
          converted_production.second = converted_production.second.
          Replace(non_terminal, current_symbol);
        // end if
        }
      // end for
      }
      first_step_productions.insert(converted_production);
    } else {
      first_step_productions.insert(current_production);
    }
  // end for
  }
  normalized_grammar.productions_ = first_step_productions;
  std::cout << "After first step:\n" << normalized_grammar << "===============\n";
  // for all (A → B1B2 . . . Bm (con m ≥ 3, Bi ∈ V ) do
  ProductionSet final_normalized_productions{normalized_grammar.productions_};
  for (const Production& current_production : normalized_grammar.productions_) {
    if (current_production.second.Length() >= 3) {
      //  Add m − 2 non-terminal symbols D1D2 . . . Dm−2;
      std::vector<char> created_non_terminals;
      for (int i{0}; i < current_production.second.Length() - 2; ++i) {
        char new_non_terminal = normalized_grammar.BiggestNonTerminal() + 1;
        normalized_grammar.non_terminal_symbols_.insert(new_non_terminal);
        created_non_terminals.emplace_back(new_non_terminal);
      }
      // Replace the production A → B1B2 . . . Bm with productions:
      // A → B1D1
      // D1 → B2D2
      // . . .
      // Dm−2 → Bm−1Bm
      std::vector<std::string> sentential_forms;
      for (int i{0}; i < created_non_terminals.size(); ++i) {
        std::string sentential_form;
        sentential_form += current_production.second.GetSymbols()[i];
        sentential_form += created_non_terminals[i];
        sentential_forms.emplace_back(sentential_form);
      }
      std::string last_sentential_form;
      last_sentential_form += current_production.second.GetSymbols()
      [current_production.second.Length() - 2];
      last_sentential_form += current_production.second.GetSymbols()
      [current_production.second.Length() - 1];
      sentential_forms.emplace_back(last_sentential_form);

      Production first_new_production{current_production.first, sentential_forms[0]};
      final_normalized_productions.insert(first_new_production);
      for (int i{1}, j{0}; i < sentential_forms.size(); ++i, ++j) {
        Production new_production{created_non_terminals[j], sentential_forms[i]};
        final_normalized_productions.insert(new_production);
      }
    }
  }
  normalized_grammar.productions_ = final_normalized_productions;
  for (const Production& production_checking : final_normalized_productions) {
    if (production_checking.second.Length() >= 3) {
      normalized_grammar.productions_.erase(normalized_grammar.productions_.
      find(production_checking.first));
    }
  }
  return normalized_grammar;
}

char Grammar::BiggestNonTerminal() const {
  char biggest_non_terminal;
  for (const auto& current_symbol : non_terminal_symbols_ ) {
    biggest_non_terminal = current_symbol;
  }
  return biggest_non_terminal;
}

bool Grammar::NormalizedProductionExists(const Production& production) const {
  for (const Production& current_production : productions_) {
    if (current_production.second.GetSymbols() == production.second.GetSymbols()) {
      return true;
    }
  }
  return false;
}

bool IsTerminal(const char symbol) {
  return std::isupper(symbol) ? true : false;
}