#include <pebble.h>
	
static Window *window;

static Layer *window_layer;

// define text layers
static TextLayer *cardvalue1_layer;
static TextLayer *cardvalue2_layer;
static TextLayer *cardsuit_layer;
static TextLayer *suitsmall1_layer;
static TextLayer *suitsmall2_layer;

// define all card values
static char *card_value_text[13] = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};

// define all suit values
static char *card_suit_text[4] = {"}","[","]","{"};

// set first card to ace of spaces
static int card_value = 0; 
static int suit_value = 0;

// draw suit on screen
void draw_suit() {
   text_layer_set_text(cardsuit_layer, card_suit_text[suit_value]);
}

void draw_suitsmall1() {
   text_layer_set_text(suitsmall1_layer, card_suit_text[suit_value]);
}

void draw_suitsmall2() {
   text_layer_set_text(suitsmall2_layer, card_suit_text[suit_value]);
}

// draw top left card value on screen
void draw_value1() {
   text_layer_set_text(cardvalue1_layer, card_value_text[card_value]);
}

// draw bottom right card value on screen
void draw_value2() {
   text_layer_set_text(cardvalue2_layer, card_value_text[card_value]);
}

// define function of up button - run backwards through deck, stopping at first card
void up_single_click_handler(ClickRecognizerRef recognizer, void* context) { 
	
  if(card_value == 0 && suit_value > 0){ 
      card_value = 12;
	  suit_value--;
  }
  else if(card_value > 0){ 
	  card_value--; 
  } 
  draw_suit();
  draw_suitsmall1();
  draw_suitsmall2();
  draw_value1();
  draw_value2();
}

// define function of down button - run forwards through deck, stopping at last card
void down_single_click_handler(ClickRecognizerRef recognizer, void* context) {
  
  if(card_value == 12 && suit_value < 3){ 
      card_value = 0;
	  suit_value++;
  }
  else if(card_value < 12 && suit_value <= 3){ 
	  card_value++; 
  } 
  draw_suit();
  draw_suitsmall1();
  draw_suitsmall2();
  draw_value1();
  draw_value2();
}


// main function for button operation 
void click_config_provider(Window *window) {
  // single UP click / repeat-on-hold config:
  window_single_click_subscribe(BUTTON_ID_UP, up_single_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_UP, 100, up_single_click_handler);
	
  // single DOWN click / repeat-on-hold config:
  window_single_click_subscribe(BUTTON_ID_DOWN, down_single_click_handler);
  window_single_repeating_click_subscribe(BUTTON_ID_DOWN, 100, down_single_click_handler);  
}

// start of main app
void handle_init(void) {
	
  window = window_create(); // create window
  window_set_fullscreen(window, true); // full screen without status
  window_stack_push(window, true /* Animated */);
  window_set_background_color(window, GColorWhite); // window background colour

  // setup layer
  window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_frame(window_layer);
	  	
  // define top left text layer
  cardvalue1_layer = text_layer_create(GRect(8, 8, 25, 20));
  text_layer_set_text_alignment(cardvalue1_layer, GTextAlignmentCenter);
  text_layer_set_text_color(cardvalue1_layer, GColorBlack);
  text_layer_set_background_color(cardvalue1_layer, GColorClear);
  text_layer_set_font(cardvalue1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CARD_CHARS_18)));
  layer_add_child(window_layer, text_layer_get_layer(cardvalue1_layer));
	
  draw_value1(); // draw first top left card value

  // define top small suit layer
  suitsmall1_layer = text_layer_create(GRect(10, 27, 20, 20));	
  text_layer_set_text_alignment(suitsmall1_layer, GTextAlignmentCenter);
  text_layer_set_text_color(suitsmall1_layer, GColorBlack);
  text_layer_set_background_color(suitsmall1_layer, GColorClear);
  text_layer_set_font(suitsmall1_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CARD_CHARS_18)));
  layer_add_child(window_layer, text_layer_get_layer(suitsmall1_layer));

  draw_suitsmall1(); // draw top small suit	
	
  // define centre suit layer
  cardsuit_layer = text_layer_create(GRect(55, 64, 40, 40));	
  text_layer_set_text_alignment(cardsuit_layer, GTextAlignmentCenter);
  text_layer_set_text_color(cardsuit_layer, GColorBlack);
  text_layer_set_background_color(cardsuit_layer, GColorClear);
  text_layer_set_font(cardsuit_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CARD_CHARS_34)));
  layer_add_child(window_layer, text_layer_get_layer(cardsuit_layer));

  draw_suit(); // draw suit	

   // define bottom small suit layer
  suitsmall2_layer = text_layer_create(GRect(113, 118, 20, 20));	
  text_layer_set_text_alignment(suitsmall2_layer, GTextAlignmentCenter);
  text_layer_set_text_color(suitsmall2_layer, GColorBlack);
  text_layer_set_background_color(suitsmall2_layer, GColorClear);
  text_layer_set_font(suitsmall2_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CARD_CHARS_18)));
  layer_add_child(window_layer, text_layer_get_layer(suitsmall2_layer));

  draw_suitsmall2(); // draw bottom small suit
	 
  // define bottom right text layer	
  cardvalue2_layer = text_layer_create(GRect(111, 138, 25, 20));
  text_layer_set_text_alignment(cardvalue2_layer, GTextAlignmentCenter);
  text_layer_set_text_color(cardvalue2_layer, GColorBlack);
  text_layer_set_background_color(cardvalue2_layer, GColorClear);
  text_layer_set_font(cardvalue2_layer, fonts_load_custom_font(resource_get_handle(RESOURCE_ID_FONT_CARD_CHARS_18)));
  layer_add_child(window_layer, text_layer_get_layer(cardvalue2_layer));

  draw_value2(); // draw first bottom right card value

  // check for button operation
  window_set_click_config_provider(window, (ClickConfigProvider) click_config_provider);	
}

// clear memory
void handle_deinit(void) {
  text_layer_destroy(cardvalue1_layer);
  text_layer_destroy(cardvalue2_layer);
  text_layer_destroy(cardsuit_layer);
  text_layer_destroy(suitsmall1_layer);
  text_layer_destroy(suitsmall2_layer);	
  window_destroy(window);
}

// The main event/run loop
int main(void) {
  handle_init();
  app_event_loop();
  handle_deinit();
}