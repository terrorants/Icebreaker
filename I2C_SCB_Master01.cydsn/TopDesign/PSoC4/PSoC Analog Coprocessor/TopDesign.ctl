-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-048 kit.
-- =============================================================================

-- === I2C master (SCB mode) ===
attribute port_location of \I2CM:scl(0)\ : label is "PORT(4,0)";
attribute port_location of \I2CM:sda(0)\ : label is "PORT(4,1)";

-- === RGB LED ===
attribute port_location of LED_ERROR(0)   : label is "PORT(1,4)";
attribute port_location of LED_SUCCESS(0) : label is "PORT(2,6)";