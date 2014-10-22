/**
 * @file bemenu.h
 *
 * Public API header.
 */

struct bm_renderer;
struct bm_menu;
struct bm_item;

#include <stdbool.h>
#include <stdint.h>

/**
 * @defgroup Library
 * @brief Library functions.
 *
 * Query library version, etc...
 */

/**
 * @defgroup Menu
 * @brief Menu container.
 *
 * Holds all the items, runs logic and gets rendered.
 */

/**
 * @defgroup Item
 * @brief Item container.
 *
 * Contains properties for visual representation of item.
 */

/**
 * @addtogroup Library
 * @{ */

/**
 * @name Library Initialization
 * @{ */

/**
 * Init bemenu.
 * Loads up the renderers.
 *
 * @return true on success, false on failure.
 */
bool bm_init(void);

/**
 * Get list of available renderers.
 *
 * @param out_nmemb Reference to uint32_t where total count of returned renderers will be stored.
 * @return Pointer to array of bm_renderer instances.
 */
const struct bm_renderer** bm_get_renderers(uint32_t *out_nmemb);

/** @} Library Initialization */

/**
 * @name Library Version
 * @{ */

/**
 * Get version of the library in 'major.minor.patch' format.
 *
 * @see @link http://semver.org/ Semantic Versioning @endlink
 *
 * @return Null terminated C "string" to version string.
 */
const char* bm_version(void);

/**  @} Library Version */

/**  @} Library */

/**
 * @addtogroup Renderer
 * @{ */

/**
 * Get name of the renderer.
 *
 * @param renderer bm_renderer instance.
 * @return Null terminated C "string" to renderer's name.
 */
const char* bm_renderer_get_name(const struct bm_renderer *renderer);

/**
 * @} Renderer */

/**
 * @addtogroup Menu
 * @{ */

/**
 * Filter mode constants for bm_menu instance filter mode.
 *
 * @link ::bm_filter_mode BM_FILTER_MODE_LAST @endlink is provided for enumerating filter modes.
 * Using it as filter mode however provides exactly same functionality as BM_FILTER_MODE_DMENU.
 */
enum bm_filter_mode {
    BM_FILTER_MODE_DMENU,
    BM_FILTER_MODE_DMENU_CASE_INSENSITIVE,
    BM_FILTER_MODE_LAST
};

/**
 * Result constants from bm_menu_run_with_key function.
 *
 * - @link ::bm_run_result BM_RUN_RESULT_RUNNING @endlink means that menu is running and thus should be still renderer && ran.
 * - @link ::bm_run_result BM_RUN_RESULT_SELECTED @endlink means that menu was closed and items were selected.
 * - @link ::bm_run_result BM_RUN_RESULT_CANCEL @endlink means that menu was closed and selection was canceled.
 */
enum bm_run_result {
    BM_RUN_RESULT_RUNNING,
    BM_RUN_RESULT_SELECTED,
    BM_RUN_RESULT_CANCEL,
};

/**
 * Key constants.
 *
 * @link ::bm_key BM_KEY_LAST @endlink is provided for enumerating keys.
 */
enum bm_key {
    BM_KEY_NONE,
    BM_KEY_UP,
    BM_KEY_DOWN,
    BM_KEY_LEFT,
    BM_KEY_RIGHT,
    BM_KEY_HOME,
    BM_KEY_END,
    BM_KEY_PAGE_UP,
    BM_KEY_PAGE_DOWN,
    BM_KEY_SHIFT_PAGE_UP,
    BM_KEY_SHIFT_PAGE_DOWN,
    BM_KEY_BACKSPACE,
    BM_KEY_DELETE,
    BM_KEY_LINE_DELETE_LEFT,
    BM_KEY_LINE_DELETE_RIGHT,
    BM_KEY_WORD_DELETE,
    BM_KEY_TAB,
    BM_KEY_ESCAPE,
    BM_KEY_RETURN,
    BM_KEY_SHIFT_RETURN,
    BM_KEY_CONTROL_RETURN,
    BM_KEY_UNICODE,
    BM_KEY_LAST
};

/**
 * @name Menu Memory
 * @{ */

/**
 * Create new bm_menu instance.
 *
 * @param renderer Name of renderer to be used for this instance, pass **NULL** for auto-detection.
 * @return bm_menu for new menu instance, **NULL** if creation failed.
 */
struct bm_menu* bm_menu_new(const char *renderer);

/**
 * Release bm_menu instance.
 *
 * @param menu bm_menu instance to be freed from memory.
 */
void bm_menu_free(struct bm_menu *menu);

/**
 * Release items inside bm_menu instance.
 *
 * @param menu bm_menu instance which items will be freed from memory.
 */
void bm_menu_free_items(struct bm_menu *menu);

/**  @} Menu Memory */

/**
 * @name Menu Properties
 * @{ */

/**
 * Set userdata pointer to bm_menu instance.
 * Userdata will be carried unmodified by the instance.
 *
 * @param menu bm_menu instance where to set userdata pointer.
 * @param userdata Pointer to userdata.
 */
void bm_menu_set_userdata(struct bm_menu *menu, void *userdata);

/**
 * Get userdata pointer from bm_menu instance.
 *
 * @param menu bm_menu instance which userdata pointer to get.
 * @return Pointer for unmodified userdata.
 */
void* bm_menu_get_userdata(struct bm_menu *menu);

/**
 * Set filter text to bm_menu instance.
 *
 * @param menu bm_menu instance where to set filter.
 * @param filter Null terminated C "string" to act as filter.
 */
void bm_menu_set_filter(struct bm_menu *menu, const char *filter);

/**
 * Get filter text from bm_menu instance.
 *
 * @param menu bm_menu instance where to get filter.
 * @return Const pointer to current filter text, may be **NULL** if empty.
 */
const char* bm_menu_get_filter(struct bm_menu *menu);

/**
 * Set active filter mode to bm_menu instance.
 *
 * @param menu bm_menu instance where to set filter mode.
 * @param mode bm_filter_mode constant.
 */
void bm_menu_set_filter_mode(struct bm_menu *menu, enum bm_filter_mode mode);

/**
 * Get active filter mode from bm_menu instance.
 *
 * @param menu bm_menu instance where to get filter mode.
 * @return bm_filter_mode constant.
 */
enum bm_filter_mode bm_menu_get_filter_mode(const struct bm_menu *menu);

/**
 * Set selection wrapping on/off.
 *
 * @param menu bm_menu instance where to toggle selection wrapping.
 * @param bool true/false.
 */
void bm_menu_set_wrap(struct bm_menu *menu, bool wrap);

/**
 * Get selection wrapping state.
 *
 * @param menu bm_menu instance where to get selection wrapping state.
 * @return int for wrap state.
 */
bool bm_menu_get_wrap(const struct bm_menu *menu);

/**
 * Set title to bm_menu instance.
 *
 * @param menu bm_menu instance where to set title.
 * @param title C "string" to set as title, can be **NULL** for empty title.
 * @return true if set was succesful, false if out of memory.
 */
bool bm_menu_set_title(struct bm_menu *menu, const char *title);

/**
 * Get title from bm_menu instance.
 *
 * @param menu bm_menu instance where to get title from.
 * @return Pointer to null terminated C "string", can be **NULL** for empty title.
 */
const char* bm_menu_get_title(const struct bm_menu *menu);

/**  @} Properties */

/**
 * @name Menu Items
 * @{ */

/**
 * Add item to bm_menu instance at specific index.
 *
 * @param menu bm_menu instance where item will be added.
 * @param item bm_item instance to add.
 * @param index Index where item will be added.
 * @return true on successful add, false on failure.
 */
bool bm_menu_add_item_at(struct bm_menu *menu, struct bm_item *item, uint32_t index);

/**
 * Add item to bm_menu instance.
 *
 * @param menu bm_menu instance where item will be added.
 * @param item bm_item instance to add.
 * @return true on successful add, false on failure.
 */
bool bm_menu_add_item(struct bm_menu *menu, struct bm_item *item);

/**
 * Remove item from bm_menu instance at specific index.
 *
 * @warning The item won't be freed, use bm_item_free to do that.
 *
 * @param menu bm_menu instance from where item will be removed.
 * @param index Index of item to remove.
 * @return true on successful add, false on failure.
 */
bool bm_menu_remove_item_at(struct bm_menu *menu, uint32_t index);

/**
 * Remove item from bm_menu instance.
 *
 * @warning The item won't be freed, use bm_item_free to do that.
 *
 * @param menu bm_menu instance from where item will be removed.
 * @param item bm_item instance to remove.
 * @return true on successful add, false on failure.
 */
bool bm_menu_remove_item(struct bm_menu *menu, struct bm_item *item);

/**
 * Highlight item in menu by index.
 *
 * @param menu bm_menu instance from where to highlight item.
 * @param index Index of item to highlight.
 * @return true on successful highlight, false on failure.
 */
bool bm_menu_set_highlighted_index(struct bm_menu *menu, uint32_t index);

/**
 * Highlight item in menu.
 *
 * @param menu bm_menu instance from where to highlight item.
 * @param item bm_item instance to highlight.
 * @return true on successful highlight, false on failure.
 */
bool bm_menu_set_highlighted_item(struct bm_menu *menu, struct bm_item *item);

/**
 * Get highlighted item from bm_menu instance.
 *
 * @warning The pointer returned by this function may be invalid after items change.
 *
 * @param menu bm_menu instance from where to get highlighted item.
 * @return Selected bm_item instance, **NULL** if none highlighted.
 */
struct bm_item* bm_menu_get_highlighted_item(const struct bm_menu *menu);

/**
 * Set selected items to bm_menu instance.
 *
 * @param menu bm_menu instance where items will be set.
 * @param items Array of bm_item pointers to set.
 * @param nmemb Total count of items in array.
 * @return true on successful set, false on failure.
 */
bool bm_menu_set_selected_items(struct bm_menu *menu, struct bm_item **items, uint32_t nmemb);

/**
 * Get selected items from bm_menu instance.
 *
 * @warning The pointer returned by this function may be invalid after selection or items change.
 *
 * @param menu bm_menu instance from where to get selected items.
 * @param out_nmemb Reference to uint32_t where total count of returned items will be stored.
 * @return Pointer to array of bm_item pointers.
 */
struct bm_item** bm_menu_get_selected_items(const struct bm_menu *menu, uint32_t *out_nmemb);

/**
 * Set items to bm_menu instance.
 * Will replace all the old items on bm_menu instance.
 *
 * If items is **NULL**, or nmemb is zero, all items will be freed from the menu.
 *
 * @param menu bm_menu instance where items will be set.
 * @param items Array of bm_item pointers to set.
 * @param nmemb Total count of items in array.
 * @return true on successful set, false on failure.
 */
bool bm_menu_set_items(struct bm_menu *menu, const struct bm_item **items, uint32_t nmemb);

/**
 * Get items from bm_menu instance.
 *
 * @warning The pointer returned by this function may be invalid after removing or adding new items.
 *
 * @param menu bm_menu instance from where to get items.
 * @param out_nmemb Reference to uint32_t where total count of returned items will be stored.
 * @return Pointer to array of bm_item pointers.
 */
struct bm_item** bm_menu_get_items(const struct bm_menu *menu, uint32_t *out_nmemb);

/**
 * Get filtered (displayed) items from bm_menu instance.
 *
 * @warning The pointer returned by this function _will_ be invalid when menu internally filters its list again.
 *          Do not store this pointer.
 *
 * @param menu bm_menu instance from where to get filtered items.
 * @param out_nmemb Reference to uint32_t where total count of returned items will be stored.
 * @return Pointer to array of bm_item pointers.
 */
struct bm_item** bm_menu_get_filtered_items(const struct bm_menu *menu, uint32_t *out_nmemb);

/**  @} Menu Items */

/**
 * @name Menu Logic
 * @{ */

/**
 * Render bm_menu instance using chosen renderer.
 *
 * @param menu bm_menu instance to be rendered.
 */
void bm_menu_render(const struct bm_menu *menu);

/**
 * Trigger filtering of menu manually.
 * This is useful when adding new items and want to dynamically see them filtered.
 *
 * Do note that filtering might be heavy, so you should only call it after batch manipulation of items.
 * Not after manipulation of each single item.
 *
 * @param menu bm_menu instance which to filter.
 */
void bm_menu_filter(struct bm_menu *menu);

/**
 * Poll key and unicode from underlying UI toolkit.
 *
 * This function will block on **curses** renderer.
 *
 * @param menu bm_menu instance from which to poll.
 * @param out_unicode Reference to uint32_t.
 * @return bm_key for polled key.
 */
enum bm_key bm_menu_poll_key(struct bm_menu *menu, uint32_t *out_unicode);

/**
 * Advances menu logic with key and unicode as input.
 *
 * @param menu bm_menu instance to be advanced.
 * @param key Key input that will advance menu logic.
 * @param unicode Unicode input that will advance menu logic.
 * @return bm_run_result for menu state.
 */
enum bm_run_result bm_menu_run_with_key(struct bm_menu *menu, enum bm_key key, uint32_t unicode);

/**  @} Menu Logic */

/**  @} Menu */

/**
 * @addtogroup Item
 * @{ */

/**
 * @name Item Memory
 * @{ */

/**
 * Allocate a new item.
 *
 * @param text Pointer to null terminated C "string", can be **NULL** for empty text.
 * @return bm_item for new item instance, **NULL** if creation failed.
 */
struct bm_item* bm_item_new(const char *text);

/**
 * Release bm_item instance.
 *
 * @param item bm_item instance to be freed from memory.
 */
void bm_item_free(struct bm_item *item);

/**  @} Item Memory */

/**
 * @name Item Properties
 * @{ */

/**
 * Set userdata pointer to bm_item instance.
 * Userdata will be carried unmodified by the instance.
 *
 * @param item bm_item instance where to set userdata pointer.
 * @param userdata Pointer to userdata.
 */
void bm_item_set_userdata(struct bm_item *item, void *userdata);

/**
 * Get userdata pointer from bm_item instance.
 *
 * @param item bm_item instance which userdata pointer to get.
 * @return Pointer for unmodified userdata.
 */
void* bm_item_get_userdata(struct bm_item *item);

/**
 * Set text to bm_item instance.
 *
 * @param item bm_item instance where to set text.
 * @param text C "string" to set as text, can be **NULL** for empty text.
 * @return true if set was succesful, false if out of memory.
 */
bool bm_item_set_text(struct bm_item *item, const char *text);

/**
 * Get text from bm_item instance.
 *
 * @param item bm_item instance where to get text from.
 * @return Pointer to null terminated C "string", can be **NULL** for empty text.
 */
const char* bm_item_get_text(const struct bm_item *item);

/**  @} Item Properties */

/**  @} Item */

/* vim: set ts=8 sw=4 tw=0 :*/