import SUPPORTED_CODES from './countryCodes'

/**
 * Global assert helper.
 */
function assert(condition, message) {
  if (!condition) {
    const composedMessage = `RnFbAccountKit: ${message}`
    throw new Error(composedMessage)
  }
}

/**
 * Assert valid types for selected option props.
 */
export function assertArray(prop, propName) {
  assert(prop === undefined || Array.isArray(prop), `'${propName}' should be an array, "${prop}" given.`)
}

export function assertString(prop, propName) {
  assert(prop === undefined || typeof prop === 'string', `'${propName}' should be a string, "${prop}" given.`)
}

/**
 * Assert all specified country codes are supported.
 */

export function assertValidityOfCountryCodes(options) {
  const { countryBlacklist, countryWhitelist, defaultCountry } = options

  Object.entries({
    countryBlacklist: countryBlacklist || [],
    countryWhitelist: countryWhitelist || [],
    defaultCountry: defaultCountry ? [defaultCountry] : [],
  }).forEach(([collectionName, collection]) => {
    collection.forEach(countryCode => {
      const label = `"${collectionName}": Invalid value found.`

      // Type check
      const type = typeof countryCode
      const typeToDisplay = Array.isArray(countryCode) ? 'array' : type
      assert(type === 'string', `${label} String expected, ${typeToDisplay} (${countryCode}) given.`)

      // Letter case check
      assert(
        countryCode === countryCode.toUpperCase(),
        `${label} Value should be in uppercase (${countryCode.toUpperCase()}), "${countryCode}" found.`
      )

      // Check, if country code is supported.
      assert(
        SUPPORTED_CODES.includes(countryCode),
        `${label} Country code "${countryCode}" in "${collectionName}" is not supported`
      )
    })
  })
}
