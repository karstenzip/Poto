export default defineNuxtConfig({
	modules: [
		"@vueuse/nuxt",
		"@nuxtjs/seo",
		"@nuxtjs/tailwindcss",
		"@nuxt/eslint"
	],
	site: {
		name: "Poto",
		url: "https://poto.karsten.zip",
		description: "Poto Image Converter",
		defaultLocale: "en"
	},
	css: ["~/assets/css/transitions.css"],
	typescript: {
		typeCheck: true
	},
	compatibilityDate: "2024-04-03",
	devtools: { enabled: true }
})
