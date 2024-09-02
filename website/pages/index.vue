<template>
	<div class="flex h-screen flex-col items-center justify-center gap-y-10">
		<h1 class="text-4xl font-bold">Poto Image Converter</h1>
		<div class="flex flex-col items-center gap-y-4">
			<Dropzone v-model="files" class="w-96" />
			<button
				type="button"
				class="rounded-lg bg-gradient-to-r from-cyan-500 to-blue-500 px-5 py-2.5 text-center text-sm font-medium text-white opacity-100 transition-all duration-300 ease-in-out focus:outline-none disabled:opacity-50 dark:from-cyan-700 dark:to-blue-700 dark:disabled:opacity-60"
				:class="{
					'hover:scale-110 hover:opacity-90': canUpload
				}"
				:disabled="!canUpload"
				@click="uploadFiles"
			>
				Convert images
			</button>
		</div>
	</div>
</template>

<script setup lang="ts">
const files = ref<Array<File>>([])

const canUpload = computed(
	() => files.value.length > 0 && files.value.length <= 5
)

async function uploadFiles() {
	if (!canUpload.value) return

	const formData = new FormData()
	files.value.forEach((file) => {
		if (file.size > 25 * 1024 * 1024) return
		formData.append("files", file)
	})
	const buffers = await $fetch("/api/convert", {
		method: "POST",
		body: formData
	})
	for (const file in buffers) {
		const blob = new Blob([new Uint8Array(buffers[file].data)], {
			type: "application/octet-stream"
		})

		const reader = new FileReader()
		reader.onload = () => {
			const a = document.createElement("a")
			a.href = reader.result as string
			a.download = file
			a.click()
		}
		reader.readAsDataURL(blob)
	}
	files.value = []
}
</script>
