-- =============================================================================
-- The following directives assign pins to the locations specific for the
-- CY8CKIT-042 kit.
-- =============================================================================

-- === I2C master (SCB mode) ===
attribute port_location of \I2CM:scl(0)\ : label is "PORT(3,0)";
attribute port_location of \I2CM:sda(0)\ : label is "PORT(3,1)";

-- === RGB LED ===
attribute port_location of LED_ERROR(0)   : label is "PORT(1,6)";
attribute port_location of LED_SUCCESS(0) : label is "PORT(0,2)";
