The included Node-RED flow is only an extract from a larger flow designed to take an input (Your Address/Street/Council Area/County etc.) and return a HEX colour code (#FF5733).

The associated code expects the payload of the GET request to only contain this HEX value. The leading # is optional as it is replaced in the arduino program.