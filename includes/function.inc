<?php
/**
 * Helper that generates a machine name using a provided human readable name.
 *
 * @param string $human_name
 *   Human readable name.
 *
 * @return string
 *   Machine name cleaned-up of any special chars.
 */
function _human_to_machine($human_readable) {
  return strtolower(preg_replace([
    '/[^a-zA-Z0-9]+/',
    '/-+/',
    '/^-+/',
    '/-+$/',
  ], ['_', '_', '', ''], $human_readable));
}