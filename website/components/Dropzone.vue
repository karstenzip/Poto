<template>
	<label
		for="dropzone"
		class="flex flex-col items-center justify-items-center rounded-lg border-2 border-dashed border-gray-300 bg-gray-50 py-16 transition-colors duration-200 hover:bg-gray-100 dark:border-gray-500 dark:bg-gray-700 dark:hover:bg-gray-800"
		:class="{
			'border-gray-400 bg-gray-100 dark:border-gray-600 dark:bg-gray-800':
				dragging
		}"
		@dragenter="dragging = !dragging"
		@dragleave="dragging = !dragging"
		@dragover.prevent
		@drop.prevent="drop"
	>
		<div class="flex flex-col items-center justify-center">
			<svg
				class="mb-4 size-8 text-gray-500 dark:text-gray-400"
				aria-hidden="true"
				xmlns="http://www.w3.org/2000/svg"
				fill="none"
				viewBox="0 0 20 16"
			>
				<path
					stroke="currentColor"
					stroke-linecap="round"
					stroke-linejoin="round"
					stroke-width="2"
					d="M13 13h3a3 3 0 0 0 0-6h-.025A5.56 5.56 0 0 0 16 6.5 5.5 5.5 0 0 0 5.207 5.021C5.137 5.017 5.071 5 5 5a4 4 0 0 0 0 8h2.167M10 15V6m0 0L8 8m2-2 2 2"
				/>
			</svg>
			<p class="mb-1 text-sm text-gray-500 dark:text-gray-400">
				<span class="font-semibold">Click to upload</span> or drag and drop
			</p>
			<p class="mb-2 text-xs text-gray-500 dark:text-gray-400">
				Click image to remove
			</p>
		</div>
		<Transition name="fade">
			<ul v-if="previewImages.length > 0">
				<TransitionGroup name="insertion">
					<img
						v-for="(image, index) in previewImages"
						:key="image.src"
						:src="image.src"
						:alt="image.title"
						class="mx-2 mt-6 inline-block size-12 cursor-pointer rounded-md"
						@click.prevent="files.splice(index, 1)"
					/>
				</TransitionGroup>
			</ul>
		</Transition>
		<input
			id="dropzone"
			ref="fileInput"
			type="file"
			multiple
			accept=".jpg,.jpeg,.png,.webp,.avif,.tiff,.tif,.gif,.svg"
			class="hidden"
			@change="fileChangeEvent"
		/>
	</label>
</template>

<script setup lang="ts">
const fileInput = ref<HTMLInputElement>()
const files = defineModel<Array<File>>({ required: true })
const previewImages = computedAsync(async () => {
	return await Promise.all(
		files.value.map((file) => {
			return new Promise<HTMLImageElement>((resolve, reject) => {
				const reader = new FileReader()
				const image = new Image(48, 48)
				reader.onload = () => {
					if (!reader.result) return
					image.title = file.name
					image.src = reader.result as string
					resolve(image)
				}
				reader.onerror = reject
				reader.readAsDataURL(file)
			})
		})
	)
}, [])

const dragging = ref(false)

async function fileInArray(file: File, array: Array<File>) {
	const fileBuffer = await file.arrayBuffer()
	return await asyncFind(
		array,
		async (f) =>
			f.name === file.name ||
			(f.size === file.size &&
				compareArrayBuffer(await f.arrayBuffer(), fileBuffer))
	)
}

async function drop(event: DragEvent) {
	dragging.value = false
	if (!event.dataTransfer?.files) return
	for (const file of event.dataTransfer.files) {
		if (files.value.length >= 5) break
		if (file.size > 25 * 1024 * 1024) continue
		if (file.type.split("/")[0] !== "image") continue
		if (await fileInArray(file, files.value)) continue

		files.value.push(file)
	}
}

async function fileChangeEvent() {
	if (
		fileInput.value &&
		fileInput.value.files &&
		fileInput.value.files.length > 0
	) {
		for (const file of fileInput.value.files) {
			if (files.value.length >= 5) break
			if (file.size > 25 * 1024 * 1024) continue
			if (file.type.split("/")[0] !== "image") continue
			if (await fileInArray(file, files.value)) continue

			files.value.push(file)
		}
		fileInput.value.value = ""
	}
}
</script>
