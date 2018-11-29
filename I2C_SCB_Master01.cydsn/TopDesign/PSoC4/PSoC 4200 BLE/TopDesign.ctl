-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-042-BLE kit.
-- =============================================================================

-- === I2C master (SCB mode) ===
attribute port_location of \I2CM:scl(0)\ : label is "PORT(3,5)";
attribute port_location of \I2CM:sda(0)\ : label is "PORT(3,4)";

-- === RGB LED ===
attribute port_location of LED_ERROR(0)   : label is "PORT(2,6)";
attribute port_location of LED_SUCCESS(0) : label is "PORT(3,6)";
